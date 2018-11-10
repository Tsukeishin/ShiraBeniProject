#include "SceneManager.h"
#include "Library/DirectInput.h"
#include "Title.h"
#include "Result.h"
#include "GameManager.h"


SCENE SceneManager::GameScene = SCENE_MAX;


//----�X�V--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̍X�V
		UpdateTitle();

		if (Keyboard::Trigger(DIK_RETURN))
		{
			SetScene(SCENE_GAME);
		}
		break;

	case SCENE_GAME:
		// �Q�[���V�[���̍X�V
		GameManager::Update();

		if (Keyboard::Trigger(DIK_RETURN))
		{
			SetScene(SCENE_RESULT);
		}
		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̍X�V
		UpdateResult();

		if (Keyboard::Trigger(DIK_RETURN))
		{
			SetScene(SCENE_TITLE);
		}
		break;
	}

	return 0;
}

//----�`��--------
void SceneManager::Draw()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̕`�揈��
		DrawTitle();

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̕`�揈��
		GameManager::Draw();

		break;

	case SCENE_RESULT:
		// ���U���g�̕`�揈��
		DrawResult();

		break;
	}
}

//----�Q�[���V�[���̍X�V�E�擾--------
SCENE SceneManager::SetScene(SCENE scene)
{
	/* �w��V�[���������ꍇ�͖߂� */
	if (scene == SCENE_MAX)
	{
		return GameScene;
	}

	/* ���݂̃V�[���̂��Еt�� */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̏I��
		UninitTitle();

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̏I��
		GameManager::Uninit();

		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̏I��
		UninitResult();

		break;
	}

	/* �V�[���̐؂�ւ� */
	GameScene = scene;

	/* ���̃V�[���̏��� */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̏�����
		InitTitle();

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̏�����
		GameManager::Init();

		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̏�����
		InitResult();

		break;

	default:
		return GameScene;
		break;
	}

	return GameScene;
}



