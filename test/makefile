SOURCE=../source

CC=gcc
ARGS=-I../include -g

t_buffer:
	$(CC) $(ARGS) $(SOURCE)/*.c ./buffer/buffer_test.c -o ./buffer/a.out
t_super:
	$(CC) $(ARGS) $(SOURCE)/*.c ./super/super_test.c -o ./super/a.out
t_bitmap:
	$(CC) $(ARGS) $(SOURCE)/*.c ./bitmap/bitmap_test.c -o ./bitmap/a.out
t_root_dir:
	$(CC) $(ARGS) $(SOURCE)/*.c ./dir_entry/root_entry_test.c -o ./dir_entry/a.out

