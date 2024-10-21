
//在Mine结构中表示地雷的符号常量
#define MINE -1

//Mine[MINE][MINE].Mark
#define Close 0
#define Open 1
#define Flags -1

//For Display()
#define Block '~'
#define MineIcon '@'
#define FlagsIcon '^'

//Mine结构最大值
#define X 9
#define Y 9

struct mine
{
	int Num;
	int Mark;
};