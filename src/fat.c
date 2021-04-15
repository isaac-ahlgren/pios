#include "fat.h"
#include "sd.h"
#include "uart.h"
#include "rprintf.h"

struct boot_sector *bs;
char bootSector[SECTOR_SIZE];
char fat_table[8*SECTOR_SIZE];

unsigned int root_sector;
unsigned int first_data_sector;


void set_offset(FILE* f, long unsigned int offset) {

    if (f) {
    
        f->offset = offset;
    }
    
}

unsigned int get_offset(FILE* f) {

    if (f) {
        
        return f->offset;
    }
    
    return 0;   
}


/*
 * Compares number of characters from strings and see
 * if they are equal. Returns 1 if true, 0 if not
 */ 
int file_strcmp(char* s1, char* s2, unsigned int bytes) {
    int ret = 1;

    for (int i = 0; i < bytes; i++) {
        
	if (s1[i] != s2[i]) {
	    ret = 0;
	    break;
	}

    }

    return ret;
}

/*
 * Turns all lower case letters to uppercase.
 * Returns uppercase letter.
 */
char to_upper(char c) {
    
    return (c >= 'a' && c <= 'z') ? c + ('A' - 'a') : c;
    
}

/*
 * Made under the assumption of a 8 or less
 * character file name and a 3 or less extension name.
 */
int get_filename(char* name_buffer, char* ext_buffer, char* path) {
    char* o_path = path;
    int ret = 0;
    int buff_i = 0;

    if (*path++ != '/') {
        return ret;
    }

    // get file name
    while (*path != '.' && *path != '\0' && *path != '/') {
	name_buffer[buff_i++] = to_upper(*path++);
    }

    // fill white space
    while (buff_i < 8) {
        name_buffer[buff_i++] = ' ';
    }

    buff_i = 0;
    // get file extension
    if (*path == '.') {
    
    	path++;
	while (*path != '\0' && *path != '/') {
	    ext_buffer[buff_i++] = to_upper(*path++);
	}
	    
    }
    
    // fill white space
    while (buff_i < 3) {
        ext_buffer[buff_i++] = ' ';
    }

    // checks if valid path
    if (*path == '\0' || *path == '/') {
        ret = path - o_path;
    }

    return ret;
}

/*
 * Initializes FAT16 file system.
 * Returns 1 on success, 0 on 
 * failure
 */
int fat_init() {
    int ret = 1;

    sd_readblock(0, (unsigned char*) bootSector, SECTOR_SIZE);
    bs = (struct boot_sector*) bootSector;

    if (bs->boot_signature != 0xaa55) {
        ret = 0;
	return ret;
    }

    if (!file_strcmp(bs->fs_type, "FAT16   ", 8)) {
	ret = 0;
	return ret;
    }
    
    sd_readblock(bs->num_reserved_sectors, (unsigned char*) fat_table, 8);

    root_sector = bs->num_fat_tables*bs->num_sectors_per_fat + bs->num_reserved_sectors + bs->num_hidden_sectors;
    
    first_data_sector = bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat) + 
    			((bs->num_root_dir_entries * 32) + (SECTOR_SIZE - 1)) / SECTOR_SIZE;
    
    return ret;
}

/*
 * Opens file for reading.
 * Returns 1 if success, 0
 * on failure.
 */
int file_open(FILE* f, char* path) {
    int ret = 1;
    unsigned int sector = root_sector;

    struct root_directory_entry* dir_buffer;
    char buffer[8*SECTOR_SIZE];
    char name_buffer[8];     // file names can be no longer than 8 bytes
    char ext_buffer[3];      // file names can be no longer than 3 bytes
    
    while (*path != '\0') {

        // parse file path
        int traveled = get_filename(name_buffer, ext_buffer, path);

        if (!traveled) {
	    ret = 0;
	    break;
	}

	path += traveled;

        // read current directory
	sd_readblock(sector, (unsigned char*) buffer, 8);
	    
	dir_buffer = (struct root_directory_entry*) buffer;
	
	int wrong_file_type = 0;
	// traverse current directory
	for (;*dir_buffer->file_name != 0; dir_buffer++) {
	        
	    // skip unused entry
	    if (*dir_buffer->file_name == 0xe5)
	        continue;
	        
	    // check if file names are the same
	    if (file_strcmp(dir_buffer->file_name, name_buffer, 8) && 
	        file_strcmp(dir_buffer->file_extension, ext_buffer, 3)) 
	    {   
	        	
	        /* 
	    	    if supposed to be file but is directory or if supposed to 
	            be directory but is a file 
	        */ 
	        if ((*path == '\0' && (dir_buffer->attribute & (1 << 4))) ||
	            (*path == '/' && !(dir_buffer->attribute & (1 << 4)))) 
	        {
	            wrong_file_type = 1;
	            break;
    		}
	       
	        sector = ((dir_buffer->cluster - 2) * bs->num_sectors_per_cluster) + first_data_sector;
	        break;
	        
	    }
        }
	    
	// error: no matching entry was found in directory
	if (wrong_file_type || *dir_buffer->file_name == 0) {
	   ret = 0;
	   break;
	}
    }
    
    if (ret) {
        f->rde = *dir_buffer;
        f->start_cluster = dir_buffer->cluster;
        f->offset = 0;
    }
    
    return ret;
}

int read_file(FILE* f, unsigned char* buf, unsigned int bytes) {
    
    unsigned int file_size = f->rde.file_size;
    unsigned int bytes_read = f->offset;
    
    // no more to be read
    if (bytes_read >= file_size) {
        return -1;
    }    
    
    unsigned int end = f->offset + bytes;
    unsigned int bytes_per_cluster = bs->num_sectors_per_cluster*bs->bytes_per_sector;
    
    unsigned short cluster = f->start_cluster + f->offset / (bs->num_sectors_per_cluster * bs->bytes_per_sector);
    unsigned short sector = ((cluster - 2) * bs->num_sectors_per_cluster) + first_data_sector;
    
    unsigned char cluster_buffer[8*SECTOR_SIZE];
    
    
    while (bytes_read < file_size && bytes_read < end) {

	// read current cluster
        sd_readblock(sector, cluster_buffer, bs->num_sectors_per_cluster);
	
	// read size of cluster, size of remaining bytes requested, or remaining bytes in the file
	for (int i = bytes_read % bytes_per_cluster; i < bytes_per_cluster && bytes_read < file_size && bytes_read < end; i++) {
	
	    *buf++ = cluster_buffer[i];
	    
	    bytes_read++;
	}

	// find next cluster
	unsigned int index = (cluster * 2) % bs->bytes_per_sector;
	cluster = *(unsigned short*)&fat_table[index];
	sector = ((cluster - 2) * bs->num_sectors_per_cluster) + first_data_sector;
	
	// end of cluster or corrupted cluster
	if (cluster >= 0xfff7) {
	    break;
	}
    }
    
    f->offset = bytes_read;

    return bytes_read;
}	

    


	    
	    
	    
	        
	        	
	        	
	        	
	  







    
