#include "SceneManager.h"
#include "Library/DirectInput.h"
#include "Title.h"
#include "Result.h"
#include "GameManager.h"


SCENE SceneManager::GameScene = SCENE_MAX;


//----更新--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの更新
		UpdateTitle();

		if (Keyboard::Trigger(DIK_RETURN))
		{
			SetScene(SCENE_GAME);
		}
		break;

	case SCENE_GAME:
		// ゲームシーンの更新
		GameManager::Update();

		if (Keyboard::Trigger(DIK_RETURN))
		{
			SetScene(SCENE_RESULT);
		}
		break;

	case SCENE_RESULT:
		// リザルトシーンの更新
		UpdateResult();

		if (Keyboard::Trigger(DIK_RETURN))
		{
			SetScene(SCENE_TITLE);
		}
		break;
	}

	return 0;
}

//----描画--------
void SceneManager::Draw()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの描画処理
		DrawTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの描画処理
		GameManager::Draw();

		break;

	case SCENE_RESULT:
		// リザルトの描画処理
		DrawResult();

		break;
	}
}

//----ゲームシーンの更新・取得--------
SCENE SceneManager::SetScene(SCENE scene)
{
	/* 指定シーンが同じ場合は戻る */
	if (scene == SCENE_MAX)
	{
		return GameScene;
	}

	/* 現在のシーンのお片付け */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの終了
		UninitTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの終了
		GameManager::Uninit();

		break;

	case SCENE_RESULT:
		// リザルトシーンの終了
		UninitResult();

		break;
	}

	/* シーンの切り替え */
	GameScene = scene;

	/* 次のシーンの準備 */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの初期化
		InitTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの初期化
		GameManager::Init();

		break;

	case SCENE_RESULT:
		// リザルトシーンの初期化
		InitResult();

		break;

	default:
		return GameScene;
		break;
	}

	return GameScene;
}



