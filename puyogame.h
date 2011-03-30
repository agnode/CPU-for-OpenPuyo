#ifndef _PUYOGAME_H_
#define _PUYOGAME_H_
#define PUYO_BOX_X0			(0)					/* ぷよ箱の始点(X座標)			!*/
#define PUYO_BOX_Y0			(0)					/* ぷよ箱の始点(Y座標)			!*/
#define PUYO_BOX_WALL_Y1	(15)				/* ぷよ箱の壁座標(下)			!*/
#define PUYO_BOX_VISIBLE_X0	(PUYO_BOX_X0 + 1)	/* ぷよ箱の可視範囲の始点(X座標)	!*/
#define PUYO_BOX_VISIBLE_Y0	(PUYO_BOX_Y0 + 3)	/* ぷよ箱の可視範囲の始点(Y座標)	!*/
#define PUYO_BOX_VISIBLE_WIDTH		(6)			/* ぷよ箱の可視範囲のサイズ(幅)	!*/
#define PUYO_BOX_VISIBLE_HEIGHT		(12)		/* ぷよ箱の可視範囲のサイズ(高さ)	!*/
#define PUYO_ACT_FIRST_X0			(3)			/* 組ぷよ0番目(X座標)	!*/
#define PUYO_ACT_FIRST_Y0			(1)			/* 組ぷよ0番目(Y座標)	!*/
#define PUYO_ACT_FIRST_X1			(3)			/* 組ぷよ1番目(X座標)	!*/
#define PUYO_ACT_FIRST_Y1			(2)			/* 組ぷよ1番目(Y座標)	!*/
#define	PUYO_EMPTY		(0x00)			/* 空				!*/
#define PUYO_RED		(0x01)			/* 赤ぷよ				!*/
#define PUYO_BLUE		(0x02)			/* 青ぷよ				!*/
#define PUYO_GREEN		(0x03)			/* 緑ぷよ				!*/
#define PUYO_PURPLE		(0x04)			/* 紫ぷよ				!*/
#define PUYO_YELLOW		(0x05)			/* 黄色ぷよ			!*/
#define PUYO_OBSTACLE	(0x80)			/* おじゃまぷよ		!*/
#define PUYO_WALL		(0xff)			/* 移動不可			!*/
#define ST_NORMAL		(0x00)			/* 通常状態					!*/
#define ST_CHAIN		(0x01)			/* 連鎖状態					!*/
#define ST_FALLING		(0x02)			/* 落下ぷよの落下状態			!*/
#define ACT_PUYO_INSIDE		(0)				/* 中心ぷよのインデックス	!*/
#define ACT_PUYO_OUTSIDE	(1)				/* 外ぷよのインデックス		!*/
typedef unsigned char PuyoColor;		/* ぷよ色						!*/
typedef short PuyoBoxID;				/* ぷよ箱のアクセスID			!*/
struct active_puyo {			/*			!*/
	int x;						/* 箱のX座標	!*/
	int y;						/* 箱のY座標	!*/
	PuyoColor color;			/* ぷよの色	!*/
};								/*			!*/
typedef struct active_puyo ActivePuyo;	/*	!*/
extern unsigned char get_status(PuyoBoxID);						/*	!*/
extern PuyoColor get_puyo(PuyoBoxID,int,int);					/*	!*/
extern const ActivePuyo* get_act_puyo(PuyoBoxID);				/*	!*/
extern const PuyoColor* get_next_puyo(PuyoBoxID);				/*	!*/
#define FLG_OFF			(0x00)		/* フラグオン			!*/
#define FLG_ON			(0x01)		/* フラグオフ			!*/
/* CPUイベントコード													!*/
#define CPU_EVENT_CLEAR			(0x00)			/* 入力をクリアする		!*/
#define CPU_EVENT_MOVE_DOWN		(0x02)			/* 下に移動する		!*/
#define CPU_EVENT_MOVE_LEFT		(0x03)			/* 左に移動する		!*/
#define CPU_EVENT_MOVE_RIGHT	(0x04)			/* 右に移動する		!*/
#define CPU_EVENT_ROTATE_LEFT	(0x05)			/* 左に旋回する		!*/
#define CPU_EVENT_ROTATE_RIGHT	(0x06)			/* 右に旋回する		!*/
#endif
