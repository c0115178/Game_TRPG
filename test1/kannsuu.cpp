#pragma once
#include "header1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include <windows.h>

//���������錾
bool Goal;
//�퓬����
bool battle;
bool tutorial = false;
bool battleAkemi = false;
bool bookDescription = false;

/*--------------------------------
�Q�[���̃��[������
�v���C���[���������͂���Ǝ��֐i��
----------------------------------*/
void explain() {
	//�����ɐ�������
	printf("���[��\n");
	printf("\t1,���~�T���̃��[��\n");
	printf("\t\t�E�u�ړ��A�A�C�e���̎擾�A�A�C�e���̒����A������߂�v����I����\n\t\t�@1�^�[�������A\n");
	printf("\t\t�E�����͈ړ�����̂Ńv���C���[�̑؍݂��镔���ɂ��o������B���̂�\n\t\t�@���Ɂu�B���v�Ɓu�퓬�v��I���ł��邪�A�u�B���v��I�������\n\t\t�@2/3�̊m���Ő������A�R�^�[�������B���s�̏ꍇ�͐퓬�ֈڍs��\n\t\t�@��B\n");
	printf("\t\t�E�����������Ԃŉ������Ȃ���I�������HP��10�񕜂���B\n");
	printf("\t\t�E�ړ���Q�������΂��ł����[�����{�����邱�Ƃ��ł���B\n\t\t�@�^�[������Ȃ��B\n");
	printf("\t2,�퓬�̃��[��\n");
	printf("\t\t�E�����ƓG�̃^�[�������݂ɌJ��Ԃ��B\n");
	printf("\t\t�E�U���͎����̍U���͂Ƒ����i�̍U���͂𑫂����_���[�W��^����B\n");
	printf("\t\t�E�퓬���ɂ͍U���̑��ɂ������ύX�ƃA�C�e�����g�����Ƃ��\�B\n");
	printf("\t\t�E������1/3�̊m���ōU���ɐ�������B\n");
	printf("\t3,�����p�j�̃��[��\n");
	printf("\t\t�E3�^�[�����Ƀ����_���ŕ����ɏo����3�^�[���؍݂���B�o�������u��\n\t\t�@�ɖ����𔭂��A�ǂ̃t���A�ɂ��邩���킩��悤�ɂȂ��Ă���B\n");
	printf("\t4,�함�j���Ɋւ��郋�[��\n");
	printf("\t\t�E�함��j�󂷂�Ƃ�1~100�̗���+�����̑����i�̍U���͂𑫂����l��\n\t\t�@90�ȏ�ɂȂ����ꍇ�ɔj��ɐ�������B�����A���s�ǂ����1�^�[��\n\t\t�@�����B\n");
	printf("\t\t�E�j�󂪎��s�����ꍇ�����̊m���Ŏ�l���̏ꏊ�ɉ�����������A\n\t\t�@���퓬�J�n�ƂȂ�B\n");
	printf("\t5,��������\n");
	printf("\t\t�E������1�K�̃h�A����E�o����B\n");
	printf("\t6,�s�k����\n");
	printf("\t\t�E�v���C���[�̂��C���Ȃ��Ȃ�B\n");
	printf("\t\t�E�`���[�g���A���Ȃǂ̓���̐퓬�ŕ�����Ɣs�k����B");

	//�����I����

	//�v���C���[�̓��͂Ŏ��֐i��
	printf("\nEnter����͂��Ă�������\n");
	enter();
}


/*-----------------------
������Seed������������
-----------------------*/
void initRandom() {
	srand((unsigned)time(NULL));
}

/*------------
�����̏�����
-------------*/
void initRoom() {

	//�n�����̏�����
	room[0].next = &room[1];
	room[0].weapon = &weapon[1];

	//�P�K�̏�����
	room[1].next = &room[2];
	room[1].next2 = &room[0];
	room[1].next3 = &room[3];
	room[1].next4 = &room[4];
	room[1].next5 = &room[7];

	//�Q�K�̏�����
	room[2].next2 = &room[1];
	room[2].next3 = &room[5];
	room[2].next4 = &room[6];

	//�}�����̏�����
	room[3].next = &room[1];
	room[3].item1 = &item[0];
	room[3].item2 = &item[4];

	//�����P�̏�����
	room[4].next = &room[1];
	room[4].item1 = &item[3];
	room[4].weapon = &weapon[2];

	//�����Q�̏�����
	room[5].next = &room[2];
	room[5].item1 = &item[1];
	room[5].item2 = &item[2];

	//�����R�̏�����
	room[6].next = &room[2];
	room[6].weapon = &weapon[3];
	room[6].locked = true;

	//���ւ̏�����
	room[7].locked = true;
}

/*-------------
��l���̏�����
---------------*/
struct player initPlayer() {
	//��l���̍\���̂̏�����
	struct player player = {
		MAX, initATK, false, false, false, &room[1], &weapon[0]
	};

	return player;
}

/*--------------
�������̏�����
---------------*/
struct monster initMonster() {
	//�������̍\���̂̏�����
	struct monster monster = {
		monMax, 40, &room[4], false
	};

	return monster;
}



/*---------------
���݂̏�Ԃ̕\��
----------------*/
void showMap(struct player *player, struct monster *monster) {
	printf("\n");
	printf("    --------\n");
	printf("    |");
	if (!room[3].item1->flag)
		printf("I");
	else
		printf(" ");
	if (player->Location->name == room[3].name)
		printf("P");
	else
		printf(" ");
	if (!room[3].item2->flag)
		printf("I");
	else
		printf(" ");
	printf("|");
	if (!room[5].item1->flag)
		printf("I");
	else
		printf(" ");
	if (player->Location->name == room[5].name)
		printf("P");
	else
		printf(" ");
	if (!room[5].item2->flag)
		printf("I");
	else
		printf(" ");
	printf("|\n");

	printf("-------------\n");
	printf("|");
	if (!room[0].weapon->flag)
		printf("W");
	else
		printf(" ");
	if (player->Location->name == room[0].name)
		printf("P");
	else
		printf(" ");
	printf(" ");
	printf("|");
	printf(" ");
	if (player->Location->name == room[1].name)
		printf("P");
	else
		printf(" ");
	printf(" ");
	printf("|");
	printf(" ");
	if (player->Location->name == room[2].name)
		printf("P");
	else
		printf(" ");
	printf(" ");
	printf("|");
	printf("\n");
	printf("-------------\n");

	printf("    |");
	if (!room[4].item1->flag)
		printf("I");
	else
		printf(" ");
	if (player->Location->name == room[4].name)
		printf("P");
	else
		printf(" ");
	if (!room[4].weapon->flag)
		printf("W");
	else
		printf(" ");
	printf("|");
	if (!room[6].weapon->flag)
		printf("W");
	else
		printf(" ");
	if (player->Location->name == room[6].name)
		printf("P");
	else
		printf(" ");
	printf(" ");
	printf("|\n");
	printf("    --------\n");

	printf("\n");
	printf("%d�^�[����  �������̏ꏊ�F%s\nHP:%d   ATK:%d\n", TURN, monster->Location->name, player->HP, player->ATK);
}

/*-------------------
0�`x-1�܂ł̐�����Ԃ�
--------------------*/
int Random(int x) {
	return rand() % x;
}

/*---------------------------
�v���C���[�����͂���������Ԃ�
----------------------------*/
char enterSomething() {
	char pp = getc(stdin);
	rewind(stdin);

	return pp;
}

/*---------------------
�����������֐�
---------------------*/
void monsterCrow(struct player *player, struct monster *monster) {
	if (!monster->defeated) {
		int q = player->Location->floor - monster->Location->floor;
		switch (q) {
		case -2:
			printf("�������̐����������ɕ�������I\n�ǂ���炩�Ȃ艓���ɂ���悤���I\n");
			break;
		case -1:
			printf("�������̐����ォ�畷������I\n�ǂ�����̊K�ɂ���悤���I\n");
			break;
		case 0:
			printf("�������̐�����������I\n�ǂ���瓯���K�ɂ���悤���I\n");
			break;
		case 1:
			printf("�������̐��������畷������I\n�ǂ���牺�̊K�ɂ���悤���I\n");
			break;
		case 2:
			printf("�������̐����������ɕ�������I\n�ǂ���炩�Ȃ艓���ɂ���悤���I\n");
			break;
		default:
			break;
		}

		char w = enterSomething();
	}
}

/*------------------------
�������ɕ������HP����
�n�����Ɉړ�
------------------------*/
void ifLose(struct player *player, struct monster *monster) {
	bool FLAG = true;

	while (FLAG) {
		printf("�N���܂����H(y/n)\n");
		char c = enterSomething();
		int z = (int)c;
		switch (z) {
		case 121:
			FLAG = false;
			break;
		case 110:
			printf("�������ɂȂ��Ă��܂����I�I\nGame Over!!\n");
			enter();
			exit(1);
			FLAG = false;
			break;
		default:
			printf("��蒼���Ă�������\n");
			break;
		}
	}
	printf("�n�����Ŗڂ��o�߂܂��B\n");
	printf("�ǂ���牻�����ɘA��Ă���ꂽ�悤�ł��B\n");

	player->HP = MAX;
	player->Location = &room[0];

	monster->HP = monMax;
	monster->Location = &room[4];
	TURN = 1;
	enter();

	if (item[1].flag) {
		struct monster akemi = {
			100, 20, NULL, false
		};

		printf("�����Ȃ艽���ɏP���|����ꂽ�I�I\n");
		battleAkemi = true;

		bool battle = true;

		while (battle) {
			battle = Battle(player, &akemi);
		}

		battleAkemi = false;
		item[1].flag = false;

		enter();
		printf("\n\n������|�����̂��Ǝv���A���Ă݂��\n");
		enter();
		printf("\n\n\n\n\n");
		printf("���Ȃ��ɏP���|�������̂͗c����̏����������B\n");
		enter();
	}

	monsterCrow(player, monster);
}

/*-----------------
�퓬�֐�(����)
-------------------*/
bool Battle(struct player *player, struct monster *monster) {
	if (player->weapon->name == weapon[1].name) {
		player->ATK = initATK + 100;
	}
	else {
		player->ATK = initATK + player->weapon->status;
	}

	printf("player HP:%d ATK:%d         monster HP:%d ATK:%d\n", player->HP, player->ATK, monster->HP, monster->ATK);

	int xx;

	xx = Random(6);

	//�v���C���[�^�[��
	//�n���}�[�ȊO
	if (player->weapon->dice == 1) {
		if (xx >= 4) {
			monster->HP -= (player->ATK) * 2;
			printf("�听���I\n");
			printf("%d�̃_���[�W!\n", (player->ATK) * 2);
			if (monster->HP <= 0) {
				printf("�����I�I\n");
				monster->defeated = true;
			}
		}
		else if (xx >= 2) {
			monster->HP -= player->ATK;
			printf("�����I\n");
			printf("%d�̃_���[�W!\n", (player->ATK));
			if (monster->HP <= 0) {
				printf("�����I�I\n");
				monster->defeated = true;
			}
		}
		else {
			printf("�v���C���[�̋�U��I\n");
		}
	}
	//�n���}�[
	else {
		if (xx >= 4) {
			printf("�听���I\n");
			monster->HP -= (player->ATK) * 2;
			printf("%d�̃_���[�W!\n", (player->ATK) * 2);
			if (monster->HP <= 0) {
				printf("�����I�I\n");
				monster->defeated = true;
			}
		}
		else {
			printf("�v���C���[�̋�U��I\n");
		}
	}
	if (!(tutorial || battleAkemi)) {
		if (monster->defeated) {
			room[6].locked = false;
			room[7].locked = false;
			printf("�ǂ������献�̊J���������������I�I\n");
			char e = enterSomething();
			return false;
		}
	}
	else {
		if (monster->defeated) {
			return false;
		}
	}
	printf("player HP:%d ATK:%d         monster HP:%d ATK:%d\n", player->HP, player->ATK, monster->HP, monster->ATK);

	Sleep(1000);
	//�����X�^�[
	if (item[0].flag) {
		printf("���C�g�̌��ŉ������������낢�ł���I�I\n");
	}
	xx = Random(6);
	if (xx >= 3) {
		if (item[0].flag == true) {
			player->HP -= (monster->ATK) * 2 / 3;
			printf("                            %d�̃_���[�W!\n", monster->ATK * 2 / 3);
		}
		else {
			player->HP -= (monster->ATK);
			printf("                            %d�̃_���[�W!\n", (monster->ATK));
		}
		//printf("player HP:%d ATK:%d            monster HP:%d ATK:%d\n", player->HP, player->ATK, monster->HP, monster->ATK);
		if (player->HP <= 0) {
			printf("�s�k�I�I\n");
			char c = enterSomething();
			if (tutorial || battleAkemi) {
				exit(1);
			}
			player->DefeatMonster = true;
			ifLose(player, monster);
			return false;
		}
	}
	else {
		printf("                            �����X�^�[�̋�U��I�I\n");
	}
	Sleep(1000);
	return true;
}

/*------------
�B���֐�
--------------*/
void hide(struct player *player, struct monster *monster) {
	if (Random(100) >= 50) {
		printf("�B��邱�Ƃɐ��������B\n");
		printf("�������͂ǂ����ֈړ������I\n");
		enter();
	}
	else {
		printf("�B��邱�ƂɎ��s�����B\n");
		printf("�������Ɍ������Ă��܂����B\n");
		enter();
		printf("�퓬�J�n\n");
		enter();
		battle = true;
		while (battle) {
			battle = Battle(player, monster);
		}
	}
}


/*----------------------
�����ύX�֐�
�莝���̑�����\����
�I�񂾑����𑕔�����
----------------------*/
void changeWeapon(struct player *player) {
	printf("�ǂ̑����ɕύX���܂����H\n");
	if (weapon[0].flag) {
		printf("1:%s\n", weapon[0].name);
	}
	else {
		printf("1:-----\n");
	}
	if (weapon[1].flag) {
		printf("2:%s\n", weapon[1].name);
	}
	else {
		printf("2:-----\n");
	}
	if (weapon[2].flag) {
		printf("3:%s\n", weapon[2].name);
	}
	else {
		printf("3:-----\n");
	}
	if (weapon[3].flag) {
		printf("4:%s\n", weapon[3].name);
	}
	else {
		printf("4:-----\n");
	}

	/*--------------------
	�v���C���[����̏o��
	----------------------*/
	printf("\n�I���� �F ");
	char x = getc(stdin);
	rewind(stdin);
	int z = (int)x;

	/*------------
	������I�񂾂�
	���̑����ɕύX
	--------------*/
	switch (z) {
	case 49:
		if (weapon[0].flag) {
			player->weapon = &weapon[0];
			printf("%s�𑕔������I\n", player->weapon->name);
		}
		else {
			printf("��蒼���Ă�������\n");
			changeWeapon(player);
		}
		break;
	case 50:
		if (weapon[1].flag) {
			player->weapon = &weapon[1];
			printf("%s�𑕔������I\n", player->weapon->name);
		}
		else {
			printf("��蒼���Ă�������\n");
			changeWeapon(player);
		}
		break;
	case 51:
		if (weapon[2].flag) {
			player->weapon = &weapon[2];
			printf("%s�𑕔������I\n", player->weapon->name);
		}
		else {
			printf("��蒼���Ă�������\n");
			changeWeapon(player);
		}
		break;
	case 52:
		if (weapon[3].flag) {
			player->weapon = &weapon[3];
			printf("%s�𑕔������I\n", player->weapon->name);
		}
		else {
			printf("��蒼���Ă�������\n");
			changeWeapon(player);
		}
		break;
	default:
		printf("��蒼���Ă�������\n");
		changeWeapon(player);
		break;
	}

}

/*-------------------------
�������Ȃ��֐�
�c��������鎞����HP10��
�iMAX�F150�j
--------------------------*/
void doNothing(struct player *player) {
	if (item[1].flag) {
		if (player->HP >= MAX) {
			printf("�����񕜂ł��Ȃ��I\n");
		}
		else {
			player->HP += 10;
			printf("HP��10�񕜂����I\n");
		}
	}
	else {
		printf("�������Ȃ�����!\n");
	}
	TURN++;
}

/*----------------------
�I�����̕\��
1�`2�s�ځi�A�C�e���j
----------------------*/
void printChoiceItem(int num, char c, struct Room *newRoom, struct Item *newItem) {
	//�ړ��悪����ΑI������\��
	if (newRoom != NULL) {
		printf("%d:%s          ", num, newRoom->name);
		//�A�C�e��������ΑI������\��
		if (newItem != NULL) {
			//�A�C�e�������łɎ����Ă�����I������\��
			if (newItem->flag) {
				printf("%c:�Q�Q�Q�Q�Q\n", c);
			}
			//�A�C�e����I�����ɕ\��
			else {
				printf("%c:%s\n", c, newItem->name);
			}
		}
		//�A�C�e�����Ȃ���ΑI������\��
		else {
			printf("%c:�Q�Q�Q�Q�Q\n", c);
		}
	}
	else {
		printf("%d:�Q�Q�Q�Q�Q      ", num);
		if (newItem != NULL) {
			if (newItem->flag) {
				printf("%c:�Q�Q�Q�Q�Q\n", c);
			}
			else {
				printf("%c:%s\n", c, newItem->name);
			}
		}
		else {
			printf("%c:�Q�Q�Q�Q�Q\n", c);
		}
	}
}


/*----------------------
�I�����̕\��
3�s�ځi����j
----------------------*/
void printChoiceWeapon(struct Room *newRoom, struct Weapon *newWeapon) {
	//�ړ��悪����ΑI������\��
	if (newRoom != NULL) {
		printf("3:%s          ", newRoom->name);
		//�A�C�e��������ΑI������\��
		if (newWeapon != NULL) {
			//�A�C�e�������łɎ����Ă�����I������\��
			if (newWeapon->flag) {
				printf("c:�Q�Q�Q�Q�Q\n");
			}
			//�A�C�e����I�����ɕ\��
			else {
				printf("c:%s\n", newWeapon->name);
			}
		}
		//�A�C�e�����Ȃ���ΑI������\��
		else {
			printf("c:�Q�Q�Q�Q�Q\n");
		}
	}
	else {
		printf("3:�Q�Q�Q�Q�Q      ");
		if (newWeapon != NULL) {
			if (newWeapon->flag) {
				printf("c:�Q�Q�Q�Q�Q\n");
			}
			else {
				if (newWeapon->name == weapon[1].name) {
					if (item[0].flag) {
						printf("c:%s\n", newWeapon->name);
					}
					else {
						printf("c:�Q�Q�Q�Q�Q\n");
					}
				}
				else {
					printf("c:%s\n", newWeapon->name);
				}
			}
		}
		else {
			printf("c:�Q�Q�Q�Q�Q\n");
		}
	}
}

/*----------------------
�I�����̕\��
4�s�ځi���֌��j
----------------------*/
void printChoiceDoor(struct Room *newRoom, struct Room *door) {
	if (newRoom != NULL) {
		printf("4:%s          ", newRoom->name);
		//���ւ�����ΑI�����ɕ\��
		if (door != NULL) {
			printf("v:%s\n", door->name);
		}
		//���ւ��Ȃ���ΑI������\��
		else {
			printf("v:�Q�Q�Q�Q�Q\n");
		}
	}
	else {
		printf("4:�Q�Q�Q�Q�Q      ");
		if (door != NULL) {
			printf("v:%s\n", door->name);
		}
		else {
			printf("v:�Q�Q�Q�Q�Q\n");
		}
	}
}

/*---------------------------------
�v���C���[���ړ�������
player->Location��newRoom�ɕύX����
---------------------------------*/
void moveRoom(struct player *player, struct Room *newRoom, struct monster *monster) {
	player->Location = newRoom;
	if (player->Location->name == monster->Location->name) {
		if (monster->defeated) {
			printf("�������̎��̂�����B\n");
		}
		else {
			printf("�����������I�����؂�Ȃ��I");
			enter();
			printf("�퓬�J�n\n");
			enter();
			battle = true;
			while (battle) {
				battle = Battle(player, monster);
			}
		}
	}
	TURN++;
	if (player->Location->name == room[7].name) {
		Goal = true;
	}
}

/*-------------------------
�A�C�e������ɓ����
newItem��flag��true�ɂ��A
description��\��������
---------------------------*/
void getItem(struct Item *newItem) {
	if (newItem->name == item[4].name) {
		if (item[1].flag) {
			newItem->flag = true;
			printf("%s����ɓ��ꂽ�I\n", newItem->name);
			printf("%s\n", newItem->description);
			bookDescription = true;
		}
		else {
			newItem->flag = true;
			printf("%s����ɓ��ꂽ�I\n", newItem->name);
			printf("�ǂ߂Ȃ�\n�N���ǂ߂�l�����邩������Ȃ�\n");
		}
	}
	else if (newItem->name == item[1].name) {
		if (item[4].flag) {
			newItem->flag = true;
			printf("%s���p�[�e�B�ɓ������I\n", newItem->name);
			printf("%s\n", newItem->description);
			printf("�{��ǂ�ł�������I\n%s\n", item[4].description);
			bookDescription = true;
		}
		else {
			newItem->flag = true;
			printf("%s���p�[�e�B�ɓ������I\n", newItem->name);
			printf("%s\n", newItem->description);
		}
	}

	else if (newItem->name == item[0].name) {
		if (bookDescription == true) {
			newItem->flag = true;
			printf("%s����ɓ��ꂽ�I\n", newItem->name);
			printf("%s\n", newItem->description);

		}
		else {
			newItem->flag = true;
			printf("%s����ɓ��ꂽ�I\n", newItem->name);
			printf("�Â��ꏊ�ł��悭������I");
		}
	}

	else {
		newItem->flag = true;
		printf("%s����ɓ��ꂽ�I\n", newItem->name);
		printf("%s\n", newItem->description);
	}
}

/*--------------------------
�h�A��j�󂷂�֐�
�j��o������
newRoom->Locked��false�ɂ���
newRoom�Ɉړ�����
----------------------------*/
void destruction(struct player *player, struct Room *newRoom, struct monster *monster) {
	if (120 <= (Random(101) + player->ATK)) {
		newRoom->locked = false;
		printf("�h�A��j�󂵁A�ʂ蔲���邱�Ƃ��ł����I\n");
		enter();
		moveRoom(player, newRoom, monster);
		TURN++;
	}
	else {
		printf("�h�A��j��ł��Ȃ������B\n");
		enter();
		TURN++;
		if (Random(2) >= 1) {
			printf("�傫�ȉ��ɋC�t����������������Ă����I\n�퓬�J�n\n");
			enter();
			monster->Location = player->Location;
			bool battle = true;
			while (battle) {
				battle = Battle(player, monster);
			}
		}
	}

}

/*---------------------------
�I�������ړ��悪�����
moveRoom�����
NULL�Ȃ�I�ђ����Ă���������\��
----------------------------*/
void selectRoom(struct player *player, struct Room *newRoom, struct monster *monster) {

	if (newRoom != NULL) {
		//�������ړ�����
		if (newRoom->locked) {
			printf("�����������Ă���悤���B\n");

			bool FLAG = true;
			while (FLAG) {
				printf("�h�A��j�󂵂܂����H(y/n)\n���s����Ɖ�����������Ă���\��������܂��B\n");
				char c = enterSomething();
				int z = (int)c;

				switch (z) {
				case 121:
					destruction(player, newRoom, monster);
					FLAG = false;
					break;
				case 110:
					FLAG = false;
					break;
				default:
					printf("��蒼���Ă��������I\n");
				}
			}
		}
		else {
			moveRoom(player, newRoom, monster);
		}
	}
	else {
		printf("��蒼���Ă�������\n");
	}

}

/*---------------------------
�I�������A�C�e���������
getItem�����
NULL�Ȃ�I�ђ����Ă���������\��
----------------------------*/
void selectItem(struct Item *newItem) {
	if (newItem != NULL) {
		if (newItem->flag) {
			printf("��蒼���Ă�������\n");
		}
		else {
			if (newItem->name == item[4].name) {
				if (item[3].flag) {
					getItem(newItem);
					TURN++;
				}
				else
				{
					bool FLAG = true;

					while (FLAG) {
						printf("�T����3�^�[��������܂�����낵���ł����H(y/n)\n");
						char c = enterSomething();
						int z = (int)c;
						switch (z) {
						case 121:
							getItem(newItem);
							TURN += 3;
							FLAG = false;
							break;
						case 110:
							FLAG = false;
							break;
						default:
							printf("��蒼���Ă�������\n");
							break;
						}
					}
				}
			}
			else {
				getItem(newItem);
				TURN++;
			}
		}
	}
	else {
		printf("��蒼���Ă�������\n");
	}
}

/*-----------------------
��ɓ��ꂽ������
�������邩����
-------------------------*/
void setWeapon(struct player *player, struct Weapon *newWeapon) {
	bool FLAG = true;
	while (FLAG) {
		printf("%s�𑕔����܂����H(y/n)", newWeapon->name);
		char c = enterSomething();
		int z = (int)c;
		switch (z) {
		case 121:
			FLAG = false;
			player->weapon = newWeapon;
			printf("%s�𑕔�����\n", newWeapon->name);
			break;
		case 110:
			FLAG = false;
			printf("�������Ȃ�����\n\n");
			break;
		default:
			printf("��蒼���Ă�������\n");
			break;
		}
	}
}

/*---------------------------
�I�������ړ��悪�����
moveRoom�����
NULL�Ȃ�I�ђ����Ă���������\��
----------------------------*/
void selectWeapon(struct Weapon *newWeapon, struct player *player) {
	if (newWeapon != NULL) {
		if (newWeapon->flag) {
			printf("��蒼���Ă�������\n");
		}
		else {
			if (newWeapon->name == weapon[1].name) {
				if (item[0].flag) {
					newWeapon->flag = true;
					TURN++;
					printf("%s����ɓ��ꂽ\n", newWeapon->name);
					enter();
					printf("%s\n", newWeapon->explain);
					enter();
					setWeapon(player, newWeapon);
					char w = enterSomething();
				}
				else {
					bool FLAG = true;

					while (FLAG) {
						printf("�T����3�^�[��������܂�����낵���ł����H(y/n)\n");
						char c = enterSomething();
						int z = (int)c;
						switch (z) {
						case 121:
							newWeapon->flag = true;
							TURN += 3;
							printf("%s����ɓ��ꂽ\n", newWeapon->name);
							enter();
							printf("%s\n", newWeapon->explain);
							enter();
							setWeapon(player, newWeapon);
							FLAG = false;
							break;
						case 110:
							FLAG = false;
							break;
						default:
							printf("��蒼���Ă�������\n");
							break;
						}
					}
				}
			}
			else {
				newWeapon->flag = true;
				TURN++;
				printf("%s����ɓ��ꂽ\n", newWeapon->name);
				enter();
				if (newWeapon->name == weapon[1].name) {
					printf("��łł��Ă���p�C�v�̂悤���B���ꂪ���L�ŏ�����Ă������킾�낤�B");
				}
				printf("%s\n", newWeapon->explain);
				enter();
				setWeapon(player, newWeapon);
				char w = enterSomething();
			}
		}
	}
	else {
		printf("��蒼���Ă�������\n");
	}
}
/*----------------------------------------------------------------
Move�֐�(�����F��l���̍\���̂̃|�C���^�Ə�������)
�s����ƕ����ɂ���A�C�e���̑I������\������
�I�������I�����ɉ������ύX��������i��F�����P��I�Ԃƕ����P�֍s��
����I�Ԃƌ�����ɓ����j
------------------------------------------------------------------*/
void Move(struct player *player, struct monster *monster) {
	//���ݒn�̕\��
	printf("���ݒn��%s�ł��B\n\n", player->Location->name);
	if (player->Location->name == room[0].name) {
		printf("���@�w�����������Ă���B\n");
	}
	enter();
	printf("�ǂ��֍s���܂����H(q�L�[�Ń��[���\��)\n");


	//�I����1�s�ڕ\��
	printChoiceItem(1, 'z', player->Location->next, player->Location->item1);
	//�I����2�s�ڕ\��
	printChoiceItem(2, 'x', player->Location->next2, player->Location->item2);
	//�I����3�s�ڕ\��
	printChoiceWeapon(player->Location->next3, player->Location->weapon);
	//�I����4�s�ڕ\��
	printChoiceDoor(player->Location->next4, player->Location->next5);
	//�I����5�s�ڕ\��
	//�u�������Ȃ��v����u������߂�v�ɕύX
	printf("5:������߂�      b:�����ύX\n");

	/*--------------------
	�v���C���[����̏o��
	----------------------*/
	printf("�I���� �F ");
	char x = enterSomething();
	int z = (int)x;

	printf("------------------------------------\n\n");

	/*---------------------------
	�I�񂾏ꏊ���ړ��\�Ȃ�i��
	�I�����ȊO��I�ԂƂ�蒼��
	-----------------------------*/
	char w;
	switch (z) {
	case 49:
		//�ړ���̕����ɉ����ď�������
		selectRoom(player, player->Location->next, monster);
		break;
	case 50:
		selectRoom(player, player->Location->next2, monster);
		break;
	case 51:
		selectRoom(player, player->Location->next3, monster);
		break;
	case 52:
		selectRoom(player, player->Location->next4, monster);
		break;
	case 53:
		//�������Ȃ�
		doNothing(player);
		w = enterSomething();
		break;
		/*----------------------------------
		�A�C�e���═���I�ԂƐ�����\�����A
		�t���O�𗧂Ă�i��������j
		------------------------------------*/
	case 122:
		selectItem(player->Location->item1);
		w = enterSomething();
		break;
	case 120:
		selectItem(player->Location->item2);
		w = enterSomething();
		break;
	case 99:
		selectWeapon(player->Location->weapon, player);
		break;
		/*---------------------------------------------------
		���ւ�I�ԂƃS�[��
		�i��X�A�����������Ă���󋵂ōs����ς���悤�ɂ���j
		----------------------------------------------------*/
	case 118:
		selectRoom(player, player->Location->next5, monster);
		break;
		/*-------------------
		�����ύX��I�Ԃ�
		changeWeapon()���Ă�
		-------------------*/
	case 98:
		changeWeapon(player);
		w = enterSomething();
		break;
		/*------------------------------
		q�L�[�������ƃ��[�����\�������
		enter�������ƏI��
		------------------------------*/
	case 113:
		explain();
		break;
	default:
		printf("��蒼���Ă�������\n");
	}
}

/*----------------------
�������̈ړ��֐�
Random()�̕Ԃ�l�ɂ���āA
�������̋��ꏊ��ύX����
-------------------------*/
void moveMonster(struct player *player, struct monster *monster) {
	int roomNum;
	struct Room *o;
	bool flag = true;

	while (flag) {
		roomNum = Random(6);
		switch (roomNum) {
		case 0:
			o = &room[0];
			break;
		case 1:
			o = &room[1];
			break;
		case 2:
			o = &room[2];
			break;
		case 3:
			o = &room[3];
			break;
		case 4:
			o = &room[4];
			break;
		case 5:
			o = &room[6];
			break;
		default:
			o = &room[4];
			break;
		}

		if (monster->Location->name != o->name) {
			monster->Location = o;
			flag = false;
		}
	}

	if (player->Location->name == monster->Location->name && !monster->defeated) {
		printf("���������߂Â��Ă���I\n�B��܂����H(y/n)");

		bool FLAG = true;

		char c;

		while (FLAG) {
			c = enterSomething();
			int z = (int)c;

			switch (z) {
			case 121:
				FLAG = false;
				hide(player, monster);
				if (player->Location->name == room[4].name) {
					monster->Location = &room[0];
				}
				else {
					monster->Location = &room[4];
				}
				break;
			case 110:
				FLAG = false;
				battle = true;
				while (battle) {
					battle = Battle(player, monster);
				}
				break;
			default:
				printf("���������߂Â��Ă���I\n�B��܂����H(y/n)");
				break;
			}
		}
	}

	monsterCrow(player, monster);
}

/*---------------------------
�^�[���J�E���g�֐�
�����^�[���ڂ����J�E���g��
3�^�[������moveMonster()���Ă�
----------------------------*/
void countTurn(struct player *player, struct monster *monster) {

	player->ATK = initATK + player->weapon->status;

	if (TURN >= 4) {
		//���������ړ�������
		if (!monster->defeated) {
			moveMonster(player, monster);
		}
		TURN = 1;
	}

}

/*----------
enter����
------------*/
void enter() {
	char c = enterSomething();
}

/*-------------
�`���[�g���A��
----------------*/
void Tutorial(struct  player *player) {
	struct monster takeshi {
		250, 40, NULL, false
	};
	tutorial = true;
	player->weapon = &weapon[1];

	printf("�E�E�E�H�H�E\n");
	enter();
	printf("�E�E�E�H�H�E\n");
	enter();
	printf("���E�H�H�H�I\n");
	enter();
	printf("�傫�Ȑ��ɂ��Ȃ��͖ڂ��o�߂܂��I\n����������n���ƕ����U�����Ă���A���̒��S�ɂ͔��������Ă��鉽���̖͗l������܂��B\n�C�ɂȂ������Ȃ��͂����ɋ߂Â��Ă����܂��B\n");
	enter();
	printf("����ƓˑR�����ɏP���܂��B\n���Ȃ��͂���ɑ΍R���邽�߂Ƃ����ɋ߂��ɓ]�����Ă����݊�̂悤�ȕ�����ɂ��܂��B\n");
	enter();
	battle = true;
	printf("�퓬�J�n�I\n");
	while (battle)
	{
		battle = Battle(player, &takeshi);
	}

	player->weapon = &weapon[0];
	enter();
	printf("�퓬�ɏ����������������Ă������Ȃ��͗c���3�l�ňꏏ�ɌÂ����~�ɒT���ɗ��Ă������Ƃ��v���o���܂��B\n�����Ă��Ȃ����P���������̐��̂��m���߂邽�߂ɂ���ɋ߂Â��܂��B\n");
	enter();
	printf("����͂��Ȃ��ƈꏏ�ɂ��̉��~�ɒT���ɗ����F�l�ł����B\n���Ȃ��͗F�l���E���Ă��܂����߈������玝���Ă������̂𓊂���΂��A�o���ւƌ������܂��B\n");
	enter();
	printf("�������o��Ɖ����l�Ȃ炴����̂̑傫�Ȕw�������̕����ւƓ����Ă����̂������܂����B\n");
	enter();
	printf("��������͎��R�T���ł��B\n");
	enter();
	printf("���~����E�o���Ă�������\n");
	enter();

	tutorial = false;
}