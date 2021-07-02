NAME            = libftprintf.a		// NAME : 최종 결과물 파일의 이름을 저장할 환경 변수
CC              = gcc			// CC : 컴파일러 이름 및 명령어를 저장할 환경 변수
CFLAGS          = -Wall -Wextra -Werror -g
                                        /* CFLAGS : 컴파일러 옵션을 저장할 변수
                                              -Wall : 모든 모호한 코딩에 대해서 경고를 보내는 옵션
                                              -Wextra : all 외의 나머지 경고도 함께 출력한다.
                                              -Werror : 모든 경고를 컴파일을 중단하는 오류로 취급한다.
                                              -g[level] : 디버깅 정보를 생성한다.
                                                      -level 0 : 디버깅 정보를 생성하지 않는다.
                                                      -level 1 : 최소한의 정보만 생성한다.
                                                      -level 3 : 추가적인 정보도 생성한다. 	*/
INCFLAGS        = -I./includes		/* INCFLAGS : 헤더파일의 기본 위치 경로를 설정하기 위한 옵션을 저장할 환경 변수 
					'I' 옵션 바로 옆에 헤더파일의 위치 경로를 붙여주면 헤더파일 인식이 가능해진다. */
AR              = ar crs
                                        /* c 옵션 : 아카이브 (라이브러리 파일) 생성.
                                           r 옵션 : 지정한 아카이브로 모듈(object 파일) 추가. 
                                                     새로운 object 파일이면 추가, 기존 파일이면 치환.
                                           s 옵션 : 아카이브 인덱스를 생성.    
                                                    아카이브 인덱스를 생성하지 않으면 링크 속도가 느려지고, 
                                                    시스템 환경에 따라서는 에러가 발생.     */
RM              = rm -rf		// RM : 삭제 명령어를 저장할 환경 변수

LIB_DIR         = ./libft		// LIB_DIR : Libft 의 위치 경로를 저장할 환경 변수

SRC_DIR         = ./srcs		// SRC_DIR : Source 파일(*.c)들의 위치 경로를 저장할 환경 변수
SRC_FILES       = ft_printf_utils.c \
                  ft_int_format.c \
                  ft_char_format.c \	// SRC_FILES : Source 파일(*.c)들의 이름 목록을 저장할 환경 변수
                  ft_tobase_n.c \
                  ft_strchr_set.c
					
SRCS            = $(addprefix $(SRC_DIR), $(SRC_FILES)) \
                ft_printf.c
                                        /* SRCS : 최종적으로 컴파일 과정에서 Source 파일들을 대입하기 위해 
                                                   Source 파일들의 경로와 이름을 조합하여 얻어낸 산출물을 저장할 환경 변수 
                                                 - "addprefix" 문법을 활용하여 어떠한 변수 또는 문자열에 접미사를 추가하여 
                                                 		해당 결과 산출물을 얻어낼 수 있도록 구현하였다.  	*/
        
OBJ_DIR         = ./					// OBJ_DIR : Object 파일들이 저장될 위치 경로를 저장할 환경 변수
OBJS            = $(SRCS:.c=.o)		/*      OBJS : 자동 매크로를 통해 SRCS 의 .c 확장자인 파일들을 
                					Object 파일들로 변환된 목록을 OBJS에 저장 */
.c.o            : $(SRCS)
        $(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@
/*      .c.o : 확장자 규칙에 의해서 make는 파일들간의 확장자를 자동으로 인식해서 필요한 작업을 수행한다.
        타켓 설정은 의존성 파일과 목적 파일을 실질적으로 만들기위한 명령어를 작성할 수 있다.
        .c.o 자동 확장자 규칙을 직접 구현하여 SRCS 환경 변수의 파일들을 의존하도록 설정하고 Source 파일들을 Object 파일로 생성하는 작업을 수행한다.
        $< : 현재의 목표 파일(Target)보다 더 최근에 갱신된 파일 이름
        $@ : 현재의 목표 파일(Target)		*/

$(NAME)         : $(OBJS)
        $(MAKE) all -C $(LIB_DIR)
        $(MAKE) -C $(LIB_DIR) bonus
        cp $(LIB_DIR)/libft.a $@
        $(AR) $@ $^
/*      $(NAME) : 최종 결과 라이브러리 파일의 타겟 설정
        .c.o 타겟에 의해 생성된 Object 파일들을 의존하도록 설정하고
        libft 파일들을 필요로 하기 때문에
        현재 라이브러리 파일을 만들기 전 
        libft 디렉토리 안에서의 make 명령을 실행하여 생성된 라이브러리를 
        현재 목표파일($(NAME) == libftprintf.a) 이름으로 복사한다.
        - $(MAKE) : make의 재귀적 사용으로써 Makefile 안에서 make 명령을 하나의 명령으로 인식하여 사용한다.
        - -C dir : 우선적으로 해당 경로로 이동하여 명령을 수행하는 make 옵션
        마지막으로 $(AR) 명령어를 통해 현재 목표 파일의 이름으로 라이브러리 파일 이름을 설정하고 의존성 파일을 자동 매크로를 통해 불러와 라이브러리 파일을 생성한다.
        $^ : 현재 Target이 의존하는 대상들의 전체 목록                          */       

all             : $(NAME)			/* all : Target의 이름을 지정하여,
                        				타겟절이 여러 개일 경우 그것들을 순서대로 한 번에 실행할 수 있다. */
clean           :
        $(MAKE) -C $(LIB_DIR) clean
        $(RM) $(OBJS)
/*      clean : -C dir 매크로 옵션을 사용하여 libft 디렉토리 위치에서 
                make clean 명령을 실행하여 libft의 Object 파일들을 제거해준다.
                현재 위치에서의 Object 파일들도 RM 환경 변수를 이용하여 제거해준다.		*/
fclean          :
        $(MAKE) -C $(LIB_DIR) fclean
        $(RM) $(OBJS)
        $(RM) $(NAME)
//      fclean : clean 매크로에서 수행하지 않은 라이브러리 파일까지 지워주는 작업을 수행
re              : fclean all
//      re : 라이브러리 파일과 Object 파일들을 모두 지워 초기화시킨 후 make 명령을 다시 실행
.PHONY          : all clean fclean re
//      .PHONY : PHONY 타겟은 해당 이름의 파일이 존재할 경우 충돌 방지를 위해 사용
