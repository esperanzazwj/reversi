#ifndef REVERSI_H_
#define REVERSI_H_
#include <memory.h>
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

namespace Reversi{
	typedef enum state_{ NONE, WHITE, BLACK } state;
	class reversi
	{
	private:
		short int rows[8];
		//Lancha modified
		int randomList[64];

	public:
		reversi()
		{
			memset(rows, 0, sizeof(rows));
		}
		reversi(reversi &rev)
		{
			memcpy(rows, rev.rows, sizeof(rows));
		}
		state get(int x, int y) //查看x,y处棋子颜色
		{
			if (((rows[x] >> y) & 1) == 0)
			{
				return NONE;
			}
			else if (((rows[x] >> (y + 8)) & 1) == 1)
			{
				return BLACK;
			}
			else
			{
				return WHITE;
			}
		}
		void set(int x, int y, state stat)//在坐标x,y处设置棋子颜色为stat
		{
			if (stat == NONE)
			{
				rows[x] &= ~(1 << y);
			}
			else{
				rows[x] |= 1 << y;
				if (stat == BLACK)
				{
					rows[x] |= 1 << (y + 8);
				}
				else
				{
					rows[x] &= ~(1 << (y + 8));
				}
			}
			
		}
		int check(int x, int y, state stat)//检查在x,y上落子，落stat颜色的子，是否可行，返回一个可翻转方向，返回0为没有可翻转的方向
		{
			int valid = 0;
			if (x<0 || x>8 || y<0 || y>8) return valid;
			if (get(x, y) != NONE) return valid;

			state stat_rev = stat == BLACK ? WHITE : BLACK;
			int xt, yt;

			//检查上下左右，对角线四个方向，一共八个方向是否可翻转
			xt = x - 1; yt = y;
			while (xt >= 0 && get(xt, yt) == stat_rev) xt--;
			if (xt < x - 1 && xt >= 0 && get(xt, yt) == stat) valid |= 1;

			xt = x + 1; yt = y;
			while (xt < 8 && get(xt, yt) == stat_rev) xt++;
			if (xt > x + 1 && xt < 8 && get(xt, yt) == stat) valid |= 1 << 1;

			xt = x; yt = y - 1;
			while (yt >= 0 && get(xt, yt) == stat_rev) yt--;
			if (yt < y - 1 && yt >= 0 && get(xt, yt) == stat) valid |= 1 << 2;

			xt = x; yt = y + 1;
			while (yt < 8 && get(xt, yt) == stat_rev) yt++;
			if (yt > y + 1 && y < 8 && get(xt, yt) == stat) valid |= 1 << 3;

			xt = x - 1; yt = y - 1;
			while (xt >= 0 && yt >= 0 && get(xt, yt) == stat_rev) { xt--; yt--; }
			if (xt < x - 1 && xt >= 0 && yt < y - 1 && yt >= 0 && get(xt, yt) == stat) valid |= 1 << 4;

			xt = x - 1; yt = y + 1;
			while (xt >= 0 && yt < 8 && get(xt, yt) == stat_rev) { xt--; yt++; }
			if (xt < x - 1 && xt >= 0 && yt > y + 1 && yt < 8 && get(xt, yt) == stat) valid |= 1 << 5;

			xt = x + 1; yt = y - 1;
			while (xt < 8 && yt >= 0 && get(xt, yt) == stat_rev) { xt++; yt--; }
			if (xt > x + 1 && xt < 8 && yt < y - 1 && yt >= 0 && get(xt, yt) == stat) valid |= 1 << 6;

			xt = x + 1; yt = y + 1;
			while (xt < 8 && yt < 8 && get(xt, yt) == stat_rev) { xt++; yt++; }
			if (xt > x + 1 && xt < 8 && yt > y + 1 && yt < 8 && get(xt, yt) == stat) valid |= 1 << 7;

			return valid;
		}
		void next(int x, int y, state stat, int valid) //前进到下一个局面，x,y是落子坐标，stat是落子颜色，valid的由check得到的可翻转方向
		{
			set(x, y, stat);

			state stat_rev = stat == BLACK ? WHITE : BLACK;
			int xt, yt;

			if ((valid & 1) != 0)
			{
				xt = x - 1; yt = y;
				while (xt >= 0 && get(xt, yt) == stat_rev)
				{
					set(xt, yt, stat);
					xt--;
				}
			}

			if ((valid & (1 << 1)) != 0)
			{
				xt = x + 1; yt = y;
				while (xt < 8 && get(xt, yt) == stat_rev)
				{
					set(xt, yt, stat);
					xt++;
				}
			}
			if ((valid & (1 << 2)) != 0)
			{
				xt = x; yt = y - 1;
				while (yt >= 0 && get(xt, yt) == stat_rev)
				{
					set(xt, yt, stat);
					yt--;
				}
			}

			if ((valid & (1 << 3)) != 0)
			{
				xt = x; yt = y + 1;
				while (yt < 8 && get(xt, yt) == stat_rev)
				{
					set(xt, yt, stat);
					yt++;
				}
			}

			if ((valid & (1 << 4)) != 0)
			{
				xt = x - 1; yt = y - 1;
				while (xt >= 0 && yt >= 0 && get(xt, yt) == stat_rev)
				{
					set(xt, yt, stat);
					xt--; yt--;
				}
			}

			if ((valid & (1 << 5)) != 0)
			{
				xt = x - 1; yt = y + 1;
				while (xt >= 0 && yt < 8 && get(xt, yt) == stat_rev)
				{
					set(xt, yt, stat);
					xt--; yt++;
				}
			}

			if ((valid & (1 << 6)) != 0)
			{
				xt = x + 1; yt = y - 1;
				while (xt < 8 && yt >= 0 && get(xt, yt) == stat_rev)
				{
					set(xt, yt, stat);
					xt++; yt--;
				}
			}

			if ((valid & (1 << 7)) != 0)
			{
				xt = x + 1; yt = y + 1;
				while (xt < 8 && yt < 8 && get(xt, yt) == stat_rev)
				{
					set(xt, yt, stat);
					xt++; yt++;
				}
			}
		}

		int rollout(state stat)//Lancha modified
		{
			int weight[64] = { 190, 40, 110, 110, 110, 110, 40, 190,
				40, 20, 105, 105, 105, 105, 20, 40,
				110, 105, 101, 101, 101, 101, 105, 110,
				110, 105, 101, 101, 101, 101, 105, 110,
				110, 105, 101, 101, 101, 101, 105, 110,
				110, 105, 101, 101, 101, 101, 105, 110,
				40, 20, 105, 105, 105, 105, 20, 40,
				190, 40, 110, 110, 110, 110, 40, 190, };

			srand((unsigned)time(NULL));
			int random_i = 0;
			int random_sum = 0;
			memset(randomList, 0, sizeof(randomList));

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (check(i, j, stat)!=0)
					{
						randomList[random_i++] = i * 8 + j;
						random_sum += weight[i * 8 + j];
					}
				}
			}
			if (random_i == 0)
			{
				cout << stat << "cannot continue,change to another" << endl;
				return 0;
			}

			double random_ans = random_sum * rand() / double(RAND_MAX);
			random_sum = 0;
			for (int cnt = 0; cnt < random_i; cnt++)
			{
				random_sum += weight[randomList[cnt]];
				if (random_ans <= random_sum)
				{
					int i = randomList[cnt] / 8;
					int j = randomList[cnt] - (randomList[cnt] / 8) * 8;
					next(i, j, stat, check(i, j, stat));
					return 1;
				}
			}

		}
		
		void print() //打印
		{
			printf("checkboard:\n\t");
			for (int i = 0; i < 8; i++)
				printf("%d\t", i);
			printf("\n");
			for (int x = 0; x < 8; x++)
			{
				printf("%d\t", x);
				for (int y = 0; y < 8; y++)
				{
					state stat = get(x, y);
					switch (stat)
					{
					case NONE:printf(" \t"); break;
					case WHITE:printf("W\t"); break;
					case BLACK:printf("B\t"); break;
					default:break;
					}
				}
				printf("\n");
			}
		}
	};
}
#endif