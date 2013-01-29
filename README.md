一道关于用炸弹如何炸老鼠的编程题目

1,题目相关说明， 详见消灭老鼠.docx

2,算法主要利用AStar实现， ruby版（ruby目录下），cpp版（cpp目录下）

3,算法实现方式

*首先实现函数最短寻路算法AStar(sp,ep,walkable)
	输入:sp为起点格子,ep为终点格子, walkable为寻路时可选的格子, 不在walkable中的格子,寻路不予考虑.
	返回值:如果寻路失败返回空值,如果寻路成功返回一个从sp到ep的格子列表 
	算法说明详见http://www.policyalmanac.org/games/aStarTutorial.htm

*其次实现函数explosion_range(bomb_pos). 
	输入:为放炸弹的格子.
	返回值:爆炸覆盖的范围.
	算法说明:
	1, 不考虑墙壁的存在, 获取炸弹的波及的所有格子 candidate
	2, 剔除candidate中的所有墙壁格子,以及bomb_pos格子
	3, 令walkable = candidate
	4, 令elect为一个空的集合,用于保存爆炸范围可覆盖到的格子
	5, 向elect中添加以及bomb_pos格子
	6, loop
	*	break 当 candidate 为空时
	*	ep = pop(candidate) 获取并删除candidate中的一个格子
	*	path = AStar(pos, ep, walkable) 获取pos到ep的最短路径
	*	删除candidate中在且于path中的格子
	*	向elect中添加path中步数小于d的格子
	end
	7, 返回elect, 即为爆炸波及到的格子
	
*最后实现获取2个炸弹放置的位置
	算法说明:
	1, all = [], 其中的每一个值表示一个炸弹的集合(这个炸弹集,都能炸到同一个老鼠),
	2, for mice in mouse 遍历房子里的所有老鼠
	*	bombs = explosion_range(mice)  获取能炸到mice的所有炸弹的集合bombs.
		(利用了爆炸的路径正向,逆向等效的原理)
	*	向all中添加bombs
	end
	3, for bomb1 in pop(all) 从all中取出一个炸弹集合,并且遍历其中所有的炸弹
	*	mouse_by_bomb1, mouse_by_bomb2 = [],[]
	*	for bombs in all
	*	*	mouse_by_bomb1 << bombs 如果bombs包含bomb1
	*	*	mouse_by_bomb2 << bombs 如果bombs没有包含bomb1
	*	end
	*	求出mouse_by_bomb2中所有炸弹集的交集valid_bomb2
	*	如果valid_bomb2不为空, 则 print bomb1, pop(valid_bomb2) 并 goto 结束
	end
	4, print -1
	5, 结束
	
4, 算法改进:
	函数explosion_range可以不用Astar来实现, 用类似膨胀的算法 应该能获取更快的速度.
	
5, 编译以及使用
	编译:
		cd cpp
		qmake Deratize.pro
		make
	使用:
		Deratize input.txt
		