
#	Names
NAME_PHILO		=	philo

#	Includes
-include make/includes.mk
-include make/srcs.mk

#	Compilation
CC				=	clang
CFLAGS				=	-Wall -Werror -Wextra -pthread -std=gnu11
AR				=	ar rcs

INCLUDES_PATH			=	./includes

SRCS_OBJS			=	$(SRCS_SOURCES:.c=.o)

#	Delete
RM				=	rm -rf

#	RULES
#		Defaults:
all:	$(NAME_PHILO)

#		Convert .c to .o
%.o:	%.c $(INCLUDES)
		@$(CC) $(CFLAGS) -I $(INCLUDES_PATH) -c $< -o $@

#		Compile Philo
$(NAME_PHILO):	$(INCLUDES) $(SRCS_OBJS)
					@$(CC) $(CFLAGS) -I $(INCLUDES_PATH) $(SRCS_OBJS) -o $(NAME_PHILO)
					@echo "Philo Created"

#		Clean
clean:
					@$(RM) $(SRCS_OBJS)
					@echo "Cleaning all .o in project!"

#		Fclean
fclean:			clean
					@$(RM) $(NAME_PHILO)
					@echo "Cleaning compiled programs!"

#		Re
re:				fclean all

#		Generate .mk (Makefile includes)
gmk:
		@find includes -name '*.h' | sed 's/^/INCLUDES += /' > make/includes.mk
		@find srcs -name '*.c' | sed 's/^/SRCS_SOURCES += /' > make/srcs.mk

#		PHONY
.PHONY:			all clean fclean re gmk
