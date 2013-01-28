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
	1, 令all为一个空集合, 保存
	2, for mice in mouse 遍历房子里的所有老鼠
	*	bombs = explosion_range(mice)  获取能炸到mice的所有炸弹的集合bombs.
		(利用了爆炸的路径正向,逆向等效的原理)
	*	向all中添加bombs
	end
	3, 令not_wall为所有的 可以放置炸弹的格子
	4, for bomb1,bomb2 in every_pair of not_wall
	*	ms_on_bomb1, ms_on_bomb2 = [],[]; 2个空集合
	*	for bombs in all
	*	*	ms_on_bomb1 << bombs 如果bombs包含bomb1
	*	*	ms_on_bomb2 << bombs 如果bombs没有包含bomb1
	*	end
	*
	*	valid = true
	*
	*	for bombs in ms_on_bomb2 
	*	*	valid = false 如果 bombs未包含bomb2
	*	end
	*
	*	print bomb1,bomb2 并 goto 结束 如果 valid为true
	end
	5, print -1
	6, 结束
	
