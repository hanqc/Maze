#pragma once
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               这段代码开过光，一定不会有BUG
//
//
//
#include <iostream>
#include <stack>
using namespace std;
struct Pos
{
	size_t _row;
	size_t _col;
};

template<size_t M, size_t N>
class Maze
{
public:
	Maze(int* maze)
	{
		for (size_t i = 0; i < M; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				_maze[i][j] = maze[i*N+j];
			}
		}
	}

	void Print()
	{
		for (size_t i = 0; i < M; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				cout<<_maze[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;

		if (!shortPath.empty())
		{
			cout<<"最短路径长度:"<<shortPath.size()<<" 出口";
			stack<Pos> tmp = shortPath;
			while (!tmp.empty())
			{
				Pos& top = tmp.top();
				printf("[%d,%d]<-", top._row, top._col);
				tmp.pop();
			}

			cout<<"入口"<<endl;
		}
	}

	bool CheckAccess(Pos next)
	{
		if (next._row < M && next._col < N
			&& _maze[next._row][next._col] == 0)
		{
			return true;
		}

		return false;
	}

	bool GetPath(Pos entry)
	{
		Pos cur, next;
		cur = entry;
		stack<Pos> path;
		path.push(entry);

		while (!path.empty())
		{
			cur = path.top(); 
			_maze[cur._row][cur._col] = 2;

			if (cur._row == M-1)
			{
				return true;
			}

			// 上
			next = cur;
			next._row -= 1;
			if (CheckAccess(next))
			{
				path.push(next);
				continue;
			}

			// 下
			next = cur;
			next._row += 1;
			if (CheckAccess(next))
			{
				path.push(next);
				continue;
			}

			// 右
			next = cur;
			next._col += 1;
			if (CheckAccess(next))
			{
				path.push(next);
				continue;
			}

			// 左
			next = cur;
			next._col -= 1;
			if (CheckAccess(next))
			{
				path.push(next);
				continue;
			}
			
			// 回溯
			path.pop();
		}

		return false;
	}

	bool CheckAccess(Pos cur, Pos next)
	{
		if ((next._row < M && next._col < N)
			&& (_maze[next._row][next._col] == 0
			|| _maze[next._row][next._col] > _maze[cur._row][cur._col]))
		{
			return true;
		}

		return false;
	}

	void GetShortPath(Pos entry, stack<Pos>& path)
	{
		path.push(entry);

		if (entry._row == M-1)
		{
			if (shortPath.empty() || path.size() < shortPath.size())
			{
				shortPath = path;
			}

			cout<<"找到一个出口"<<"["<<entry._row<<","<<entry._col<<"]"<<endl;
			path.pop();
			return;
		}

		// 上
		Pos next;
		next = entry;
		next._row -= 1;
		if (CheckAccess(entry, next))
		{
			_maze[next._row][next._col] = _maze[entry._row][entry._col]+1;
			GetShortPath(next, path);
		}

		// 右
		next = entry;
		next._col += 1;
		if (CheckAccess(entry, next))
		{
			_maze[next._row][next._col] = _maze[entry._row][entry._col]+1;
			GetShortPath(next, path);
		}

		// 下
		next = entry;
		next._row += 1;
		if (CheckAccess(entry, next))
		{
			_maze[next._row][next._col] = _maze[entry._row][entry._col]+1;
			GetShortPath(next, path);
		}


		next = entry;
		next._col -= 1;
		if (CheckAccess(entry, next))
		{
			_maze[next._row][next._col] = _maze[entry._row][entry._col]+1;
			GetShortPath(next, path);
		}

		path.pop();
	}

	void GetPathR(Pos entry)
	{
		_maze[entry._row][entry._col] = 2;
		if (entry._row == M-1)
		{
			cout<<"找到一个出口"<<"["<<entry._row<<","<<entry._col<<"]"<<endl;
			return;
		}

		Pos next;
		next = entry;
		next._row -= 1;
		if (CheckAccess(next))
		{
			GetPathR(next);
		}

		next = entry;
		next._row += 1;
		if (CheckAccess(next))
		{
			GetPathR(next);
		}

		next = entry;
		next._col += 1;
		if (CheckAccess(next))
		{
			GetPathR(next);
		}

		next = entry;
		next._col -= 1;
		if (CheckAccess(next))
		{
			GetPathR(next);
		}
	}

protected:
	int _maze[M][N];
	stack<Pos> shortPath;
};

void TestMaze()
{
	/*int mazeArray[10][10] = 
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{2,0,0,0,0,0,0,1,1,1},
		{1,1,0,1,1,1,0,1,1,1},
		{1,1,0,0,0,0,0,1,1,1},
		{1,1,1,1,1,0,1,1,1,1},
		{1,1,1,1,1,0,1,1,1,1},
		{1,1,1,1,1,0,1,1,1,1},
		{1,1,1,1,1,0,1,1,1,1},
		{1,1,1,1,1,0,1,1,1,1}
	};*/

	int mazeArray[10][10] = 
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,1,1,1,1,1,1},
		{1,1,0,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,1,1,1,1},
		{1,1,0,1,1,0,1,1,1,1},
		{1,1,0,1,1,0,1,1,1,1},
		{1,1,0,1,1,0,1,1,1,1},
		{1,1,0,1,1,0,1,1,1,1},
		{1,1,0,1,1,0,1,1,1,1}
	};

	Maze<10, 10> maze((int*)mazeArray);
	maze.Print();
	Pos entry = {2, 0};

	stack<Pos> path;
	maze.GetShortPath(entry, path);
	
	maze.Print();
}