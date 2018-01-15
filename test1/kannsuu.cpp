#pragma once
#include "header1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include <windows.h>

//勝利条件宣言
bool Goal;
//戦闘条件
bool battle;
bool tutorial = false;
bool battleAkemi = false;
bool bookDescription = false;

/*--------------------------------
ゲームのルール説明
プレイヤーが何か入力すると次へ進む
----------------------------------*/
void explain() {
	//ここに説明文↓
	printf("ルール\n");
	printf("\t1,屋敷探索のルール\n");
	printf("\t\t・「移動、アイテムの取得、アイテムの調査、息を潜める」から選択し\n\t\t　1ターン消費する、\n");
	printf("\t\t・怪物は移動するのでプレイヤーの滞在する部屋にも出現する。そのと\n\t\t　きに「隠れる」と「戦闘」を選択できるが、「隠れる」を選択すると\n\t\t　2/3の確率で成功し、３ターン消費する。失敗の場合は戦闘へ移行す\n\t\t　る。\n");
	printf("\t\t・女性がいる状態で何もしないを選択するとHPを10回復する。\n");
	printf("\t\t・移動中Qを押せばいつでもルールを閲覧することができる。\n\t\t　ターン所費なし。\n");
	printf("\t2,戦闘のルール\n");
	printf("\t\t・自分と敵のターンを交互に繰り返す。\n");
	printf("\t\t・攻撃は自分の攻撃力と装備品の攻撃力を足したダメージを与える。\n");
	printf("\t\t・戦闘中には攻撃の他にも装備変更とアイテムを使うことが可能。\n");
	printf("\t\t・怪物は1/3の確率で攻撃に成功する。\n");
	printf("\t3,怪物徘徊のルール\n");
	printf("\t\t・3ターン毎にランダムで部屋に出現し3ターン滞在する。出現した瞬間\n\t\t　に鳴き声を発し、どのフロアにいるかがわかるようになっている。\n");
	printf("\t4,器物破損に関するルール\n");
	printf("\t\t・器物を破壊するとき1~100の乱数+自分の装備品の攻撃力を足した値が\n\t\t　90以上になった場合に破壊に成功する。成功、失敗どちらも1ターン\n\t\t　消費する。\n");
	printf("\t\t・破壊が失敗した場合半分の確率で主人公の場所に化け物が現れ、\n\t\t　即戦闘開始となる。\n");
	printf("\t5,勝利条件\n");
	printf("\t\t・部屋の1階のドアから脱出する。\n");
	printf("\t6,敗北条件\n");
	printf("\t\t・プレイヤーのやる気がなくなる。\n");
	printf("\t\t・チュートリアルなどの特定の戦闘で負けると敗北する。");

	//説明終了↑

	//プレイヤーの入力で次へ進む
	printf("\nEnterを入力してください\n");
	enter();
}


/*-----------------------
乱数のSeedを初期化する
-----------------------*/
void initRandom() {
	srand((unsigned)time(NULL));
}

/*------------
部屋の初期化
-------------*/
void initRoom() {

	//地下室の初期化
	room[0].next = &room[1];
	room[0].weapon = &weapon[1];

	//１階の初期化
	room[1].next = &room[2];
	room[1].next2 = &room[0];
	room[1].next3 = &room[3];
	room[1].next4 = &room[4];
	room[1].next5 = &room[7];

	//２階の初期化
	room[2].next2 = &room[1];
	room[2].next3 = &room[5];
	room[2].next4 = &room[6];

	//図書室の初期化
	room[3].next = &room[1];
	room[3].item1 = &item[0];
	room[3].item2 = &item[4];

	//部屋１の初期化
	room[4].next = &room[1];
	room[4].item1 = &item[3];
	room[4].weapon = &weapon[2];

	//部屋２の初期化
	room[5].next = &room[2];
	room[5].item1 = &item[1];
	room[5].item2 = &item[2];

	//部屋３の初期化
	room[6].next = &room[2];
	room[6].weapon = &weapon[3];
	room[6].locked = true;

	//玄関の初期化
	room[7].locked = true;
}

/*-------------
主人公の初期化
---------------*/
struct player initPlayer() {
	//主人公の構造体の初期化
	struct player player = {
		MAX, initATK, false, false, false, &room[1], &weapon[0]
	};

	return player;
}

/*--------------
化け物の初期化
---------------*/
struct monster initMonster() {
	//化け物の構造体の初期化
	struct monster monster = {
		monMax, 40, &room[4], false
	};

	return monster;
}



/*---------------
現在の状態の表示
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
	printf("%dターン目  化け物の場所：%s\nHP:%d   ATK:%d\n", TURN, monster->Location->name, player->HP, player->ATK);
}

/*-------------------
0～x-1までの整数を返す
--------------------*/
int Random(int x) {
	return rand() % x;
}

/*---------------------------
プレイヤーが入力した文字を返す
----------------------------*/
char enterSomething() {
	char pp = getc(stdin);
	rewind(stdin);

	return pp;
}

/*---------------------
化け物が鳴く関数
---------------------*/
void monsterCrow(struct player *player, struct monster *monster) {
	if (!monster->defeated) {
		int q = player->Location->floor - monster->Location->floor;
		switch (q) {
		case -2:
			printf("化け物の声がかすかに聞こえる！\nどうやらかなり遠くにいるようだ！\n");
			break;
		case -1:
			printf("化け物の声が上から聞こえる！\nどうやら上の階にいるようだ！\n");
			break;
		case 0:
			printf("化け物の声が聞こえる！\nどうやら同じ階にいるようだ！\n");
			break;
		case 1:
			printf("化け物の声が下から聞こえる！\nどうやら下の階にいるようだ！\n");
			break;
		case 2:
			printf("化け物の声がかすかに聞こえる！\nどうやらかなり遠くにいるようだ！\n");
			break;
		default:
			break;
		}

		char w = enterSomething();
	}
}

/*------------------------
化け物に負けるとHPを回復
地下室に移動
------------------------*/
void ifLose(struct player *player, struct monster *monster) {
	bool FLAG = true;

	while (FLAG) {
		printf("起きますか？(y/n)\n");
		char c = enterSomething();
		int z = (int)c;
		switch (z) {
		case 121:
			FLAG = false;
			break;
		case 110:
			printf("化け物になってしまった！！\nGame Over!!\n");
			enter();
			exit(1);
			FLAG = false;
			break;
		default:
			printf("やり直してください\n");
			break;
		}
	}
	printf("地下室で目が覚めます。\n");
	printf("どうやら化け物に連れてこられたようです。\n");

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

		printf("いきなり何かに襲い掛かられた！！\n");
		battleAkemi = true;

		bool battle = true;

		while (battle) {
			battle = Battle(player, &akemi);
		}

		battleAkemi = false;
		item[1].flag = false;

		enter();
		printf("\n\n化物を倒したのかと思い、見てみると\n");
		enter();
		printf("\n\n\n\n\n");
		printf("あなたに襲い掛かったのは幼馴染の女性だった。\n");
		enter();
	}

	monsterCrow(player, monster);
}

/*-----------------
戦闘関数(自動)
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

	//プレイヤーターン
	//ハンマー以外
	if (player->weapon->dice == 1) {
		if (xx >= 4) {
			monster->HP -= (player->ATK) * 2;
			printf("大成功！\n");
			printf("%dのダメージ!\n", (player->ATK) * 2);
			if (monster->HP <= 0) {
				printf("勝利！！\n");
				monster->defeated = true;
			}
		}
		else if (xx >= 2) {
			monster->HP -= player->ATK;
			printf("成功！\n");
			printf("%dのダメージ!\n", (player->ATK));
			if (monster->HP <= 0) {
				printf("勝利！！\n");
				monster->defeated = true;
			}
		}
		else {
			printf("プレイヤーの空振り！\n");
		}
	}
	//ハンマー
	else {
		if (xx >= 4) {
			printf("大成功！\n");
			monster->HP -= (player->ATK) * 2;
			printf("%dのダメージ!\n", (player->ATK) * 2);
			if (monster->HP <= 0) {
				printf("勝利！！\n");
				monster->defeated = true;
			}
		}
		else {
			printf("プレイヤーの空振り！\n");
		}
	}
	if (!(tutorial || battleAkemi)) {
		if (monster->defeated) {
			room[6].locked = false;
			room[7].locked = false;
			printf("どこかから鍵の開く音が聞こえた！！\n");
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
	//モンスター
	if (item[0].flag) {
		printf("ライトの光で化け物がたじろいでいる！！\n");
	}
	xx = Random(6);
	if (xx >= 3) {
		if (item[0].flag == true) {
			player->HP -= (monster->ATK) * 2 / 3;
			printf("                            %dのダメージ!\n", monster->ATK * 2 / 3);
		}
		else {
			player->HP -= (monster->ATK);
			printf("                            %dのダメージ!\n", (monster->ATK));
		}
		//printf("player HP:%d ATK:%d            monster HP:%d ATK:%d\n", player->HP, player->ATK, monster->HP, monster->ATK);
		if (player->HP <= 0) {
			printf("敗北！！\n");
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
		printf("                            モンスターの空振り！！\n");
	}
	Sleep(1000);
	return true;
}

/*------------
隠れる関数
--------------*/
void hide(struct player *player, struct monster *monster) {
	if (Random(100) >= 50) {
		printf("隠れることに成功した。\n");
		printf("化け物はどこかへ移動した！\n");
		enter();
	}
	else {
		printf("隠れることに失敗した。\n");
		printf("化け物に見つかってしまった。\n");
		enter();
		printf("戦闘開始\n");
		enter();
		battle = true;
		while (battle) {
			battle = Battle(player, monster);
		}
	}
}


/*----------------------
装備変更関数
手持ちの装備を表示し
選んだ装備を装備する
----------------------*/
void changeWeapon(struct player *player) {
	printf("どの装備に変更しますか？\n");
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
	プレイヤーからの出力
	----------------------*/
	printf("\n選択肢 ： ");
	char x = getc(stdin);
	rewind(stdin);
	int z = (int)x;

	/*------------
	装備を選んだら
	その装備に変更
	--------------*/
	switch (z) {
	case 49:
		if (weapon[0].flag) {
			player->weapon = &weapon[0];
			printf("%sを装備した！\n", player->weapon->name);
		}
		else {
			printf("やり直してください\n");
			changeWeapon(player);
		}
		break;
	case 50:
		if (weapon[1].flag) {
			player->weapon = &weapon[1];
			printf("%sを装備した！\n", player->weapon->name);
		}
		else {
			printf("やり直してください\n");
			changeWeapon(player);
		}
		break;
	case 51:
		if (weapon[2].flag) {
			player->weapon = &weapon[2];
			printf("%sを装備した！\n", player->weapon->name);
		}
		else {
			printf("やり直してください\n");
			changeWeapon(player);
		}
		break;
	case 52:
		if (weapon[3].flag) {
			player->weapon = &weapon[3];
			printf("%sを装備した！\n", player->weapon->name);
		}
		else {
			printf("やり直してください\n");
			changeWeapon(player);
		}
		break;
	default:
		printf("やり直してください\n");
		changeWeapon(player);
		break;
	}

}

/*-------------------------
何もしない関数
幼馴染がいる時だけHP10回復
（MAX：150）
--------------------------*/
void doNothing(struct player *player) {
	if (item[1].flag) {
		if (player->HP >= MAX) {
			printf("もう回復できない！\n");
		}
		else {
			player->HP += 10;
			printf("HPが10回復した！\n");
		}
	}
	else {
		printf("何もしなかった!\n");
	}
	TURN++;
}

/*----------------------
選択肢の表示
1～2行目（アイテム）
----------------------*/
void printChoiceItem(int num, char c, struct Room *newRoom, struct Item *newItem) {
	//移動先があれば選択肢を表示
	if (newRoom != NULL) {
		printf("%d:%s          ", num, newRoom->name);
		//アイテムがあれば選択肢を表示
		if (newItem != NULL) {
			//アイテムをすでに持っていたら選択肢を表示
			if (newItem->flag) {
				printf("%c:＿＿＿＿＿\n", c);
			}
			//アイテムを選択肢に表示
			else {
				printf("%c:%s\n", c, newItem->name);
			}
		}
		//アイテムがなければ選択肢を表示
		else {
			printf("%c:＿＿＿＿＿\n", c);
		}
	}
	else {
		printf("%d:＿＿＿＿＿      ", num);
		if (newItem != NULL) {
			if (newItem->flag) {
				printf("%c:＿＿＿＿＿\n", c);
			}
			else {
				printf("%c:%s\n", c, newItem->name);
			}
		}
		else {
			printf("%c:＿＿＿＿＿\n", c);
		}
	}
}


/*----------------------
選択肢の表示
3行目（武器）
----------------------*/
void printChoiceWeapon(struct Room *newRoom, struct Weapon *newWeapon) {
	//移動先があれば選択肢を表示
	if (newRoom != NULL) {
		printf("3:%s          ", newRoom->name);
		//アイテムがあれば選択肢を表示
		if (newWeapon != NULL) {
			//アイテムをすでに持っていたら選択肢を表示
			if (newWeapon->flag) {
				printf("c:＿＿＿＿＿\n");
			}
			//アイテムを選択肢に表示
			else {
				printf("c:%s\n", newWeapon->name);
			}
		}
		//アイテムがなければ選択肢を表示
		else {
			printf("c:＿＿＿＿＿\n");
		}
	}
	else {
		printf("3:＿＿＿＿＿      ");
		if (newWeapon != NULL) {
			if (newWeapon->flag) {
				printf("c:＿＿＿＿＿\n");
			}
			else {
				if (newWeapon->name == weapon[1].name) {
					if (item[0].flag) {
						printf("c:%s\n", newWeapon->name);
					}
					else {
						printf("c:＿＿＿＿＿\n");
					}
				}
				else {
					printf("c:%s\n", newWeapon->name);
				}
			}
		}
		else {
			printf("c:＿＿＿＿＿\n");
		}
	}
}

/*----------------------
選択肢の表示
4行目（玄関口）
----------------------*/
void printChoiceDoor(struct Room *newRoom, struct Room *door) {
	if (newRoom != NULL) {
		printf("4:%s          ", newRoom->name);
		//玄関があれば選択肢に表示
		if (door != NULL) {
			printf("v:%s\n", door->name);
		}
		//玄関がなければ選択肢を表示
		else {
			printf("v:＿＿＿＿＿\n");
		}
	}
	else {
		printf("4:＿＿＿＿＿      ");
		if (door != NULL) {
			printf("v:%s\n", door->name);
		}
		else {
			printf("v:＿＿＿＿＿\n");
		}
	}
}

/*---------------------------------
プレイヤーを移動させる
player->LocationをnewRoomに変更する
---------------------------------*/
void moveRoom(struct player *player, struct Room *newRoom, struct monster *monster) {
	player->Location = newRoom;
	if (player->Location->name == monster->Location->name) {
		if (monster->defeated) {
			printf("化け物の死体がある。\n");
		}
		else {
			printf("化物がいた！逃げ切れない！");
			enter();
			printf("戦闘開始\n");
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
アイテムを手に入れる
newItemのflagをtrueにし、
descriptionを表示させる
---------------------------*/
void getItem(struct Item *newItem) {
	if (newItem->name == item[4].name) {
		if (item[1].flag) {
			newItem->flag = true;
			printf("%sを手に入れた！\n", newItem->name);
			printf("%s\n", newItem->description);
			bookDescription = true;
		}
		else {
			newItem->flag = true;
			printf("%sを手に入れた！\n", newItem->name);
			printf("読めない\n誰か読める人がいるかもしれない\n");
		}
	}
	else if (newItem->name == item[1].name) {
		if (item[4].flag) {
			newItem->flag = true;
			printf("%sがパーティに入った！\n", newItem->name);
			printf("%s\n", newItem->description);
			printf("本を読んでもらった！\n%s\n", item[4].description);
			bookDescription = true;
		}
		else {
			newItem->flag = true;
			printf("%sがパーティに入った！\n", newItem->name);
			printf("%s\n", newItem->description);
		}
	}

	else if (newItem->name == item[0].name) {
		if (bookDescription == true) {
			newItem->flag = true;
			printf("%sを手に入れた！\n", newItem->name);
			printf("%s\n", newItem->description);

		}
		else {
			newItem->flag = true;
			printf("%sを手に入れた！\n", newItem->name);
			printf("暗い場所でもよく見える！");
		}
	}

	else {
		newItem->flag = true;
		printf("%sを手に入れた！\n", newItem->name);
		printf("%s\n", newItem->description);
	}
}

/*--------------------------
ドアを破壊する関数
破壊出来たら
newRoom->Lockedをfalseにして
newRoomに移動する
----------------------------*/
void destruction(struct player *player, struct Room *newRoom, struct monster *monster) {
	if (120 <= (Random(101) + player->ATK)) {
		newRoom->locked = false;
		printf("ドアを破壊し、通り抜けることができた！\n");
		enter();
		moveRoom(player, newRoom, monster);
		TURN++;
	}
	else {
		printf("ドアを破壊できなかった。\n");
		enter();
		TURN++;
		if (Random(2) >= 1) {
			printf("大きな音に気付いた化け物がやってきた！\n戦闘開始\n");
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
選択した移動先があれば
moveRoomをよび
NULLなら選び直してくださいを表示
----------------------------*/
void selectRoom(struct player *player, struct Room *newRoom, struct monster *monster) {

	if (newRoom != NULL) {
		//部屋を移動する
		if (newRoom->locked) {
			printf("鍵がかかっているようだ。\n");

			bool FLAG = true;
			while (FLAG) {
				printf("ドアを破壊しますか？(y/n)\n失敗すると化け物がやってくる可能性があります。\n");
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
					printf("やり直してください！\n");
				}
			}
		}
		else {
			moveRoom(player, newRoom, monster);
		}
	}
	else {
		printf("やり直してください\n");
	}

}

/*---------------------------
選択したアイテムがあれば
getItemをよび
NULLなら選び直してくださいを表示
----------------------------*/
void selectItem(struct Item *newItem) {
	if (newItem != NULL) {
		if (newItem->flag) {
			printf("やり直してください\n");
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
						printf("探索に3ターンかかりますがよろしいですか？(y/n)\n");
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
							printf("やり直してください\n");
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
		printf("やり直してください\n");
	}
}

/*-----------------------
手に入れた装備を
装備するか聞く
-------------------------*/
void setWeapon(struct player *player, struct Weapon *newWeapon) {
	bool FLAG = true;
	while (FLAG) {
		printf("%sを装備しますか？(y/n)", newWeapon->name);
		char c = enterSomething();
		int z = (int)c;
		switch (z) {
		case 121:
			FLAG = false;
			player->weapon = newWeapon;
			printf("%sを装備した\n", newWeapon->name);
			break;
		case 110:
			FLAG = false;
			printf("装備しなかった\n\n");
			break;
		default:
			printf("やり直してください\n");
			break;
		}
	}
}

/*---------------------------
選択した移動先があれば
moveRoomをよび
NULLなら選び直してくださいを表示
----------------------------*/
void selectWeapon(struct Weapon *newWeapon, struct player *player) {
	if (newWeapon != NULL) {
		if (newWeapon->flag) {
			printf("やり直してください\n");
		}
		else {
			if (newWeapon->name == weapon[1].name) {
				if (item[0].flag) {
					newWeapon->flag = true;
					TURN++;
					printf("%sを手に入れた\n", newWeapon->name);
					enter();
					printf("%s\n", newWeapon->explain);
					enter();
					setWeapon(player, newWeapon);
					char w = enterSomething();
				}
				else {
					bool FLAG = true;

					while (FLAG) {
						printf("探索に3ターンかかりますがよろしいですか？(y/n)\n");
						char c = enterSomething();
						int z = (int)c;
						switch (z) {
						case 121:
							newWeapon->flag = true;
							TURN += 3;
							printf("%sを手に入れた\n", newWeapon->name);
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
							printf("やり直してください\n");
							break;
						}
					}
				}
			}
			else {
				newWeapon->flag = true;
				TURN++;
				printf("%sを手に入れた\n", newWeapon->name);
				enter();
				if (newWeapon->name == weapon[1].name) {
					printf("銀でできているパイプのようだ。これが日記で書かれていた武器だろう。");
				}
				printf("%s\n", newWeapon->explain);
				enter();
				setWeapon(player, newWeapon);
				char w = enterSomething();
			}
		}
	}
	else {
		printf("やり直してください\n");
	}
}
/*----------------------------------------------------------------
Move関数(引数：主人公の構造体のポインタと勝利条件)
行き先と部屋にあるアイテムの選択肢を表示する
選択した選択肢に沿った変更を加える（例：部屋１を選ぶと部屋１へ行く
剣を選ぶと剣を手に入れる）
------------------------------------------------------------------*/
void Move(struct player *player, struct monster *monster) {
	//現在地の表示
	printf("現在地は%sです。\n\n", player->Location->name);
	if (player->Location->name == room[0].name) {
		printf("魔法陣が薄く光っている。\n");
	}
	enter();
	printf("どこへ行きますか？(qキーでルール表示)\n");


	//選択肢1行目表示
	printChoiceItem(1, 'z', player->Location->next, player->Location->item1);
	//選択肢2行目表示
	printChoiceItem(2, 'x', player->Location->next2, player->Location->item2);
	//選択肢3行目表示
	printChoiceWeapon(player->Location->next3, player->Location->weapon);
	//選択肢4行目表示
	printChoiceDoor(player->Location->next4, player->Location->next5);
	//選択肢5行目表示
	//「何もしない」から「息を潜める」に変更
	printf("5:息を潜める      b:装備変更\n");

	/*--------------------
	プレイヤーからの出力
	----------------------*/
	printf("選択肢 ： ");
	char x = enterSomething();
	int z = (int)x;

	printf("------------------------------------\n\n");

	/*---------------------------
	選んだ場所が移動可能なら進む
	選択肢以外を選ぶとやり直し
	-----------------------------*/
	char w;
	switch (z) {
	case 49:
		//移動先の部屋に応じて処理する
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
		//何もしない
		doNothing(player);
		w = enterSomething();
		break;
		/*----------------------------------
		アイテムや武器を選ぶと説明を表示し、
		フラグを立てる（所持する）
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
		玄関を選ぶとゴール
		（後々、鍵がかかっている状況で行動を変えるようにする）
		----------------------------------------------------*/
	case 118:
		selectRoom(player, player->Location->next5, monster);
		break;
		/*-------------------
		装備変更を選ぶと
		changeWeapon()を呼ぶ
		-------------------*/
	case 98:
		changeWeapon(player);
		w = enterSomething();
		break;
		/*------------------------------
		qキーを押すとルールが表示される
		enterを押すと終了
		------------------------------*/
	case 113:
		explain();
		break;
	default:
		printf("やり直してください\n");
	}
}

/*----------------------
化け物の移動関数
Random()の返り値によって、
化け物の居場所を変更する
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
		printf("化け物が近づいてくる！\n隠れますか？(y/n)");

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
				printf("化け物が近づいてくる！\n隠れますか？(y/n)");
				break;
			}
		}
	}

	monsterCrow(player, monster);
}

/*---------------------------
ターンカウント関数
今何ターン目かをカウントし
3ターン毎にmoveMonster()を呼ぶ
----------------------------*/
void countTurn(struct player *player, struct monster *monster) {

	player->ATK = initATK + player->weapon->status;

	if (TURN >= 4) {
		//化け物を移動させる
		if (!monster->defeated) {
			moveMonster(player, monster);
		}
		TURN = 1;
	}

}

/*----------
enter入力
------------*/
void enter() {
	char c = enterSomething();
}

/*-------------
チュートリアル
----------------*/
void Tutorial(struct  player *player) {
	struct monster takeshi {
		250, 40, NULL, false
	};
	tutorial = true;
	player->weapon = &weapon[1];

	printf("・・・ォォ・\n");
	enter();
	printf("・・ウォォ・\n");
	enter();
	printf("ヴウォォォ！\n");
	enter();
	printf("大きな声にあなたは目が覚めます！\nあたりを見渡すと物が散乱しており、床の中心には薄く光っている何かの模様があります。\n気になったあなたはそこに近づいていきます。\n");
	enter();
	printf("すると突然何かに襲われます。\nあなたはそれに対抗するためとっさに近くに転がっていた鈍器のような物を手にします。\n");
	enter();
	battle = true;
	printf("戦闘開始！\n");
	while (battle)
	{
		battle = Battle(player, &takeshi);
	}

	player->weapon = &weapon[0];
	enter();
	printf("戦闘に勝ち少し落ち着いてきたあなたは幼馴染3人で一緒に古い屋敷に探検に来ていたことを思い出します。\nそしてあなたを襲った何かの正体を確かめるためにそれに近づきます。\n");
	enter();
	printf("それはあなたと一緒にこの屋敷に探検に来た友人でした。\nあなたは友人を殺してしまった罪悪感から持っていたものを投げ飛ばし、出口へと向かいます。\n");
	enter();
	printf("部屋を出ると何か人ならざるものの大きな背中が奥の部屋へと入っていくのが見えました。\n");
	enter();
	printf("ここからは自由探索です。\n");
	enter();
	printf("屋敷から脱出してください\n");
	enter();

	tutorial = false;
}