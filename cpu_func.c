/**
 * CPU処理
 *
 * @author agnode
 * @date 2011/03/04
 */
#include <string.h>
#include "puyogame.h"

/**
 * @brief CPU処理
 * スレッドで定期的に呼ばれる。
 * ここには、1回のCPUの思考を記述する。
 * 思考結果、イベントコードを返却し、動作を通知する。
 *
 * @return CPUのイベントコード
 * @author agnode
 * @date 2011/03/04
 * @attention なし
 */
int cpu_think(PuyoBoxID id)
{
	int ecode = CPU_EVENT_CLEAR;
	int acode = random() % 50;
	PuyoColor boundary[PUYO_BOX_VISIBLE_WIDTH] = {0};	/* ぷよの境界線 */
	const ActivePuyo* act_puyo = get_act_puyo(id);
	PuyoColor puyo_color = PUYO_EMPTY;					/* ぷよの色 */
	int invest_boundary_end_cnt = 0;					/* 境界線調査終了カウンタ */
	int x = 0;											/* X座標走査カウンタ */
	int y = 0;											/* Y座標走査カウンタ */
	static unsigned char decision_making_flg = FLG_OFF;	/* 意思決定フラグ */
	static int decision_x = 0;							/* 決定した位置(X座標) */
	static int prev_y0 = 0;

	/* ランダム行動 */
#if 0
	switch (acode) {
		case 0:
			ecode = CPU_EVENT_ROTATE_LEFT;
			break;
		case 1:
			ecode = CPU_EVENT_MOVE_LEFT;
			break;
		case 2:
			ecode = CPU_EVENT_MOVE_RIGHT;
			break;
		default:
			break;
	}
#endif

	/* 再度意思決定を行う */
	if (act_puyo[ACT_PUYO_INSIDE].y == PUYO_ACT_FIRST_Y0) {
		/* 初期座標ではない場合、意思決定したぷよが着地したと判断 */
		if (prev_y0 != PUYO_ACT_FIRST_Y0) {
			/* 意思決定フラグを消す */
			if (decision_making_flg == FLG_ON) {
				decision_making_flg = FLG_OFF;
				/* 境界をPUYO_EMPTYで埋める */
				memset(boundary, PUYO_EMPTY, sizeof(boundary));
			}
		}
	}

	/* 意思決定モード */
	if (decision_making_flg == FLG_OFF) {
		/* ぷよの境界線を取得する */
		for (y = PUYO_BOX_WALL_Y1 - 1; y >= 0; y--) {
			invest_boundary_end_cnt = 0;
			for (x = PUYO_BOX_VISIBLE_X0; x < (PUYO_BOX_VISIBLE_WIDTH + PUYO_BOX_VISIBLE_X0); x++) {
				/* (x,y)座標のぷよの色を取得する */
				puyo_color = get_puyo(id, x, y);

				switch (puyo_color) {
					case PUYO_RED:
					case PUYO_BLUE:
					case PUYO_GREEN:
					case PUYO_PURPLE:
					case PUYO_YELLOW:
					case PUYO_OBSTACLE:
						/* 色のある場合、保存する */
						boundary[x - PUYO_BOX_VISIBLE_X0] = puyo_color;
						break;
					case PUYO_EMPTY:
						/* PUYO_EMPTY数をカウント */
						invest_boundary_end_cnt++;
						break;
					default:
						break;
				}
#if 0
				printf("%02x ", boundary[x]);
#endif
			}
#if 0
			printf("\n");
#endif
			/* 列が全てPUYO_EMPTYだったため、調査終了 */
			if (invest_boundary_end_cnt >= PUYO_BOX_VISIBLE_WIDTH) {
				break;
			}
		}

#if 0
		/* 境界の色を確認する(デバッグ) */
		for (x = PUYO_BOX_VISIBLE_WIDTH - 1; x >= 0 ; x--) {
			printf("%02x ", boundary[x]);
		}
		printf("\n", boundary[x]);
#endif
		/* 境界と同じ色を探す */
		for (x = PUYO_BOX_VISIBLE_WIDTH - 1; x >= 0 ; x--) {
			/* 同じ色の場所を発見した */
			if (boundary[x] == act_puyo[ACT_PUYO_INSIDE].color) {
				decision_x = x + PUYO_BOX_VISIBLE_X0;
				break;
			}
		}
		/* 見つからなかった */
		if (x < 0) {
			decision_x = -1;
			/* 対象の色とは異なる場所に決定する */
			for (x = PUYO_BOX_VISIBLE_WIDTH - 1; x >= 0 ; x--) {
				switch (boundary[x]) {
					case PUYO_EMPTY:
					case PUYO_OBSTACLE:
						/* 空かおじゃまぷよがあればその位置に決定する */
						decision_x = x + PUYO_BOX_VISIBLE_X0;
						break;
					default:
						break;
				}
				/* 位置が決定されたため、終了する */
				if (decision_x >= 0) {
					break;
				}
#if 0
				printf("xn = %d\n", decision_x);
#endif
			}
			/* 位置が決定されていない場合 */
			if (decision_x < 0) {
				/* 一番右に決定する */
				decision_x = PUYO_BOX_VISIBLE_WIDTH;
			}
		}
#if 0
		printf("x1 = %d\n", decision_x);
#endif
		decision_making_flg = FLG_ON;
	}
	/* 決定した位置へ動作中 */
	else {
		if (decision_x == PUYO_BOX_VISIBLE_X0) {
			/* 一番左を決定した場合 */
			if (act_puyo[ACT_PUYO_INSIDE].x >= act_puyo[ACT_PUYO_OUTSIDE].x) {
				/* 外ぷよを中心ぷよの右に配置する */
				ecode = CPU_EVENT_ROTATE_LEFT;
			}
			else {
				/* 一番左に移動する */
				if (act_puyo[ACT_PUYO_INSIDE].x > decision_x) {
					ecode = CPU_EVENT_MOVE_LEFT;
				}
				else {
					/* 移動完了しているため、処理しない */
				}
			}
		}
		else if (decision_x == PUYO_BOX_VISIBLE_WIDTH) {
			/* 一番右を決定した場合 */
			if (act_puyo[ACT_PUYO_INSIDE].x <= act_puyo[ACT_PUYO_OUTSIDE].x) {
				/* 外ぷよを中心ぷよの左に配置する */
				ecode = CPU_EVENT_ROTATE_RIGHT;
			}
			else {
				/* 一番左に移動する */
				if (act_puyo[ACT_PUYO_INSIDE].x < decision_x) {
					ecode = CPU_EVENT_MOVE_RIGHT;
				}
				else {
					/* 移動完了しているため、処理しない */
				}
			}
		}
		else {
			/* 上記以外 */
			if (act_puyo[ACT_PUYO_INSIDE].x >= act_puyo[ACT_PUYO_OUTSIDE].x) {
				/* 外ぷよを中心ぷよの右に配置する */
				ecode = CPU_EVENT_ROTATE_LEFT;
			}
			else {
				if (act_puyo[ACT_PUYO_INSIDE].x > decision_x) {
					/* 決定した位置が左にあるため、左に移動する */
					ecode = CPU_EVENT_MOVE_LEFT;
				}
				else if (act_puyo[ACT_PUYO_INSIDE].x < decision_x) {
					/* 決定した位置が右にあるため、右に移動する */
					ecode = CPU_EVENT_MOVE_RIGHT;
				}
				else {
					/* 移動完了しているため、処理しない */
				}
			}
		}
	}

	/* 前回の座標を保存しておく */
	prev_y0 = act_puyo[ACT_PUYO_INSIDE].y;

    return ecode;
}
