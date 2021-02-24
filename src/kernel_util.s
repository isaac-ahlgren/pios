
.text
.globl get_except_lvl
.type  get_except_lvl,%function

/* -- int get_except_lvl() */
get_except_lvl:
    mrs x0, CurrentEL
    ret lr
