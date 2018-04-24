#include "reversi.h"
#include<iostream>
using namespace Reversi;
using namespace std;
int simulation(reversi &rev, state cur);//0Æ½¾Ö£¬1°×Ê¤£¬2ºÚÊ¤

int main()
{
	reversi rev;
	//rev.print();
	rev.set(3, 3, BLACK);
	rev.set(4, 4, BLACK);
	rev.set(3, 4, WHITE);
	rev.set(4, 3, WHITE);
	rev.print();
	state cur = BLACK;
	/*while (1)
	{
		if (cur == BLACK)
		{
			cout << "Black turn:" << endl;
			cout << "input x,y:" << endl;
			int x, y;
			cin >> x >> y;
			if (x == -1)
				break;
			int  valid = rev.check(x, y, cur);
			if (valid != 0)
			{
				rev.next(x, y, cur, valid);
				rev.print();
				cur = cur == BLACK ? WHITE : BLACK;
			}
			else
			{
				cout << "you cannot do this" << endl;
			}
		}
		else
		{
			cout << "WHITE turn:" << endl;
			rev.rollout(WHITE);
			rev.print();
			cur = cur == BLACK ? WHITE : BLACK;
		}
		
	

	}*/
	cout << simulation(rev, cur) <<"win!"<< endl;
	system("pause");
	return 0;
}

int simulation(reversi &rev,state cur)//0Æ½¾Ö£¬1°×Ê¤£¬2ºÚÊ¤
{
	reversi tmp = reversi(rev);
	while (1)
	{
		if (tmp.rollout(cur))
		{
			cur = cur == BLACK ? WHITE : BLACK;
			tmp.print();
			continue;
		}
		else
		{
			cur = cur == BLACK ? WHITE : BLACK;
			if (tmp.rollout(cur))
			{
				cur = cur == BLACK ? WHITE : BLACK;
				tmp.print();
				continue;
			}
			else break;
		}
	}

	int cnt_black = 0, cnt_white = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//cout << tmp.get(i, j) << endl;
			if (tmp.get(i, j) == WHITE) 
				cnt_white++;
			else if (tmp.get(i, j) == BLACK)
				cnt_black++;
		}
	}
	cout << "WHITE:" << cnt_white << " BLACK:" << cnt_black << endl;
	return cnt_black>cnt_white ? 2 : (cnt_black == cnt_white ? 0 : 1);
}