SRC += muse.c
SRC += vimmode.c

# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LINK_TIME_OPTIMIZATION_ENABLE = yes
COMMAND_ENABLE = no
RGB_MATRIX_ENABLE = no
CONSOLE_ENABLE = yes
