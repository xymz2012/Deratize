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
	1, ��allΪһ���ռ���, ����
	2, for mice in mouse �������������������
	*	bombs = explosion_range(mice)  ��ȡ��ը��mice������ը���ļ���bombs.
		(�����˱�ը��·������,�����Ч��ԭ��)
	*	��all�����bombs
	end
	3, ��not_wallΪ���е� ���Է���ը���ĸ���
	4, for bomb1,bomb2 in every_pair of not_wall
	*	ms_on_bomb1, ms_on_bomb2 = [],[]; 2���ռ���
	*	for bombs in all
	*	*	ms_on_bomb1 << bombs ���bombs����bomb1
	*	*	ms_on_bomb2 << bombs ���bombsû�а���bomb1
	*	end
	*
	*	valid = true
	*
	*	for bombs in ms_on_bomb2 
	*	*	valid = false ��� bombsδ����bomb2
	*	end
	*
	*	print bomb1,bomb2 �� goto ���� ��� validΪtrue
	end
	5, print -1
	6, ����
	
