COM_COLOR   = \033[1;34m
CLEAN_COLOR	= \033[1;31m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"
CLEAN_STRING = "Cleaning"

NAME=omykolai.filler
FLAGS= -Wall -Wextra -Werror -I. -c
LIBDIR=libft/
LIB=$(LIBDIR)libft.a
PRINTFDIR=ft_printf/
PRINTF=$(PRINTFDIR)libftprintf.a
SRCS=src/filler.c\
	 src/read/read.c\
	 src/read/read_funcs.c\
	 src/read/read_cells/read_map.c\
	 src/read/read_cells/read_piece.c\
	 src/read/read_cells/read_cells_funcs.c\
	 src/read/read_cells/cell_pos.c\
	 src/process/process.c\
	 src/process/cluster_num.c\
	 src/process/result/piece_queue.c\
	 src/process/result/piece_val.c\
	 src/process/result/process_cell.c\
	 src/process/result/piece_check.c\
	 src/process/result/process_result.c\
	 src/process/distance/border_dist.c\
	 src/process/distance/pivotal_cells.c\
	 src/process/distance/best_surround.c\
	 src/process/distance/player_queue.c\
	 src/process/distance/opponent_queue.c\
	 src/process/distance/list_funcs.c\
	 get_next_line/get_next_line.c
OBJS=$(SRCS:%.c=%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(PRINTF) $(OBJS)
	@gcc -o $(NAME) $(OBJS) $(LIB) $(PRINTF)> $@.log; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
        elif [ -s $@.log ]; then \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
        else  \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
        fi; \
        rm -f $@.log; \
        exit $$RESULT

%.o: %.c
	@gcc $(FLAGS) $< -o $@> $@.log; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler: $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
        elif [ -s $@.log ]; then \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler: $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
        fi; \
        rm -f $@.log; \
        exit $$RESULT

$(LIB):
	@make -C $(LIBDIR)

$(PRINTF):
	@make -C $(PRINTFDIR)

clean:
	@-rm -f $(OBJS)
	@make -C $(LIBDIR) fclean
	@make -C $(PRINTFDIR) fclean
	@printf "%-20b%b" "$(CLEAN_COLOR)$(CLEAN_STRING)" "$(OBJ_COLOR)filler$(NO_COLOR)\n"

fclean: clean
	@-rm -f $(NAME)
	@printf "%-20b%b" "$(CLEAN_COLOR)Removing" "$(OBJ_COLOR)omykolai.filler$(NO_COLOR)\n"

re: fclean all
