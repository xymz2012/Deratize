һ��������ը�����ը����ı����Ŀ

1,��Ŀ���˵���� �����������.docx

2,�㷨��Ҫ����AStarʵ�֣� ruby�棨rubyĿ¼�£���cpp�棨cppĿ¼�£�

3,�㷨ʵ�ַ�ʽ

*����ʵ�ֺ������Ѱ·�㷨AStar(sp,ep,walkable)
	����:spΪ������,epΪ�յ����, walkableΪѰ·ʱ��ѡ�ĸ���, ����walkable�еĸ���,Ѱ·���迼��.
	����ֵ:���Ѱ·ʧ�ܷ��ؿ�ֵ,���Ѱ·�ɹ�����һ����sp��ep�ĸ����б� 
	�㷨˵�����http://www.policyalmanac.org/games/aStarTutorial.htm

*���ʵ�ֺ���explosion_range(bomb_pos). 
	����:Ϊ��ը���ĸ���.
	����ֵ:��ը���ǵķ�Χ.
	�㷨˵��:
	1, ������ǽ�ڵĴ���, ��ȡը���Ĳ��������и��� candidate
	2, �޳�candidate�е�����ǽ�ڸ���,�Լ�bomb_pos����
	3, ��walkable = candidate
	4, ��electΪһ���յļ���,���ڱ��汬ը��Χ�ɸ��ǵ��ĸ���
	5, ��elect������Լ�bomb_pos����
	6, loop
	*	break �� candidate Ϊ��ʱ
	*	ep = pop(candidate) ��ȡ��ɾ��candidate�е�һ������
	*	path = AStar(pos, ep, walkable) ��ȡpos��ep�����·��
	*	ɾ��candidate��������path�еĸ���
	*	��elect�����path�в���С��d�ĸ���
	end
	7, ����elect, ��Ϊ��ը�������ĸ���
	
*���ʵ�ֻ�ȡ2��ը�����õ�λ��
	�㷨˵��:
	1, all = [], ���е�ÿһ��ֵ��ʾһ��ը���ļ���(���ը����,����ը��ͬһ������),
	2, for mice in mouse �������������������
	*	bombs = explosion_range(mice)  ��ȡ��ը��mice������ը���ļ���bombs.
		(�����˱�ը��·������,�����Ч��ԭ��)
	*	��all�����bombs
	end
	3, for bomb1 in pop(all) ��all��ȡ��һ��ը������,���ұ����������е�ը��
	*	mouse_by_bomb1, mouse_by_bomb2 = [],[]
	*	for bombs in all
	*	*	mouse_by_bomb1 << bombs ���bombs����bomb1
	*	*	mouse_by_bomb2 << bombs ���bombsû�а���bomb1
	*	end
	*	���mouse_by_bomb2������ը�����Ľ���valid_bomb2
	*	���valid_bomb2��Ϊ��, �� print bomb1, pop(valid_bomb2) �� goto ����
	end
	4, print -1
	5, ����
	
4, �㷨�Ľ�:
	����explosion_range���Բ���Astar��ʵ��, ���������͵��㷨 Ӧ���ܻ�ȡ������ٶ�.
	
5, �����Լ�ʹ��
	����:
		cd cpp
		qmake Deratize.pro
		make
	ʹ��:
		Deratize input.txt
		