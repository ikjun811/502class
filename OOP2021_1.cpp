#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <Windows.h>

// https://github.com/beomjoo90/OOP2021 , branch: 1학기


//이전 부분은 GitHub 사용 미숙으로 기록 X
// 4/23 수업 : 함수화
// 4/26 수업 : 구조체 사용 준비
// 4/30 수업 : 구조체 정리 역할맞게 함수 정리(떠넘기기)

using namespace std;

const int directionToLeft = 0;
const int directionToRight = 1;
const int screenSize = 80;

struct Screen {
	int		size;
	char*	canvas;
};

struct Player {
	char	face[20];
	int		pos;
	int		nRemaining;
};

struct Enemy {
	char	face[20];
	int		pos;
	int		nRemaining;
};

struct Bullet {
	bool	isReady;
	int		pos;
	int		direction;
};

struct Bullets {
	int		nBullets;
	Bullet*	bullets;
};



void screen_init(Screen* screen,unsigned int size)
{
	if (screen == nullptr) return;
	if (size == 0) size = 80;
	screen->size = size;
	screen->canvas = (char*)malloc(sizeof(char) * (size + 1));
}
void screen_clear(Screen* screen)
{
	memset(screen->canvas, ' ', screen->size);
}
void screen_draw(Screen* screen, int pos, const char* face)
{
	strncpy( &(screen->canvas[pos]), face, strlen(face));
}
// 함수 이름이 같아도 입력파라미터 차이가 있으면 다르게 봄
void screen_draw(Screen* screen, int pos, char face)
{
	if (pos < 0 || pos >= screen->size) return;
	(screen->canvas[pos]) = face;
}
void screen_render(Screen* screen)
{
	screen->canvas[screen->size] = '\0';  // render screen
	printf("%s\r", screen->canvas);
}
void screen_deinit(Screen* screen)
{
	free(screen->canvas);
	screen->canvas = nullptr;
	screen->size = 0;
}



void player_init(Player* player, int pos, const char* face)
{
	player->pos = pos;
	strcpy(player->face, face);
	player->nRemaining = 0;
}
void player_move(Player* player, int direction)
{
	if (direction == directionToLeft) --(player.pos);
	else ++(player.pos);
}
void player_fire(Player* player, Enemy* enemy, Bullets* bullets) 
{
	int i = findUnusedBullet(areReady, nBullets);
	if (i == -1) return;

	areReady[i] = false; // make the ready bullet in used
	if (playerPos < enemyPos) directions[i] = directionToRight;
	else directions[i] = directionToLeft;

	if (directions[i] == directionToRight) bulletPositions[i] = playerPos + strlen(playerFace) - 1;
	else bulletPositions[i] = playerPos;
}
void player_update(Player* player, const char* Face) {}
void player_draw(Player* player, Screen* screen)
{
	screen_draw(screen)
}



void enemy_init(Enemy* enemy, int pos, const char* face)
{
	enemy->pos = pos;
	strcpy(enemy->face, face);
	enemy->nRemaining = 0;
}
void enemy_move(Enemy* enemy, int direction) 
{
	if (direction == directionToLeft) --(enemy.pos);
	else ++(enemy.pos);
}
void enemy_update(Enemy* enemy, const char* Face) {}
void enemy_draw(Enemy* enemy, Screen* screen)
{
	screen_draw(screen, enemy->pos )
}

void moveLeft(int* position)
{
	--(*position);
}
void moveRight(int* position)
{
	++(*position);
}
void update(char* face, int* nRemaining, const char* target)
{
	// update player
	if (*nRemaining > 0) {
		--(*nRemaining);
		if ((*nRemaining) == 0) { // 1초가 지났을 때
			strcpy(face, target);
		}
	}
}


void bullet_init(Bullet* bullet)
{
	bullet->isReady = true;
	bullet->pos = 0;
	//
}
void bullet_draw(Bullet* bullet, Screen* screen)
{
	if (bullet->isReady == true) return;
	screen_draw(screen, bullet->pos, '-');
}
void bullets_init(Bullets* bullets,unsigned int nBullets)
{
	if (nBullets == 0) nBullets = 80;
	bullets->nBullets = nBullets;
	bullets->bullets = (Bullet*)malloc(sizeof(Bullet) * nBullets);

	for (int i = 0; i < nBullets; i++) {
		Bullet* bullet = &(bullets->bullets[i]);
		bullet_init(bullet);
	}
}
void bullets_update(Bullets* bullets, Player* player, Enemy* enemy) {}

void bullets_draw(Bullets* bullets, Screen* screen)
{
	for (int i = 0; i < bullets->nBullets[i]; i++)
	{
		Bullet* bullet = &(bullets.bullets[i]);

		if (bulletPositions[i] >= 0 && bulletPositions[i] < screenSize) {
			screen_draw(&screen, bulletPositions[i], '-'); // draw bullet
		}
	}
}
void bullets_deinit(Bullets* bullets)
{
	free(bullets->bullets);
	bullets->bullets = nullptr;
	bullets->nBullets = 0;
}



void updateBullets(bool areReady[], int bulletPositions[], int directions[], const int nBullets, 
	char* playerFace, int* nPlayerRemaining,
	char* enemyFace, int enemyPos, int* nEnemyRemaining)
{
	// update all bullets
	for (int i = 0; i < nBullets; i++)
	{
		if (areReady[i] == true) continue;

		// isReady[i] == false
		directions[i] == directionToRight ? bulletPositions[i]++ : bulletPositions[i]--; // move bullet automatically
		if ((directions[i] == directionToLeft && enemyPos + strlen(enemyFace) - 1 == bulletPositions[i])
			|| (directions[i] == directionToRight && enemyPos == bulletPositions[i])) { // 적이 총알을 맞았을 때
			strcpy(enemyFace, "(T_T)");
			*nEnemyRemaining = 10;
			strcpy(playerFace, "\\(^_^)/");
			*nPlayerRemaining = 30;
			areReady[i] = true;
		}

		if (bulletPositions[i] < 0 || bulletPositions[i] >= screenSize) {
			areReady[i] = true;
		}
	}
}

int findUnusedBullet(bool* areReady, const int nBullets)
{
	
	for (int i = 0; i < nBullets; i++)
	{
		if (areReady[i] == true) return i;
	}

	return -1;
}









int main()
{	
	Screen screen; // 
	Player player;
	Enemy enemy;
	Bullets bullets;

	int major;
	int minor;


	screen_init(&screen, 80);
	player_init(&player, 50, "(-_-)");
	enemy_init(&enemy, 10, "(`_#)");
	bullets_init(&bullets, 80);



	// game loop
	bool isLooping = true;
	while (isLooping == true) {
		screen_clear(&screen);		   		

		// handle inputs
		if (_kbhit() ) {
			
			major = _getch();
			switch (major) {
			case 'q' : //quit
				isLooping = false;
			case ' ':
				player_fire(&player, &enemy, &bullets);
				break;
			case 224: // arrow key, function key pressed
				minor = _getch();
				switch (minor) {
				case 75: // left
					player_move(&player, directionToLeft);
					break;
				case 77: // right
					player_move(&player, directionToRight);
					break;
				case 72: // up
					enemy_move(&enemy, directionToLeft);
					break;
				case 80: // down
					enemy_move(&enemy, directionToRight);
					break;
				}
				break;
			}
			///
		}

		player_update(&player, "(-_-)");
		enemy_update(&enemy, "(`_#)");
		bullets_update(&bullets, &player, &enemy);

		player_draw(&player, &screen);
		screen_draw(&screen, player.pos, player.face);
		screen_draw(&screen, enemy.pos, enemy.face);
		bullet_draw(&bullets, &screen);

		screen_render(&screen);
	


		Sleep(100);
	}
	printf("\nGame Over\n");

	bullets_deinit(&bullets);
	screen_deinit(&screen);
	
	return 0;
}