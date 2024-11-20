#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "effect.h"

#define MAX_PARTICLE (256)	// �ő�p�[�e�B�N����

// �p�[�e�B�N���^�C�v
typedef enum
{
	PATITYPE_RADIATION = 0,
	PATITYPE_MAX
}PATITIPE;

// �p�[�e�B�N���\����
typedef struct
{
	EFFECT effect;		// �G�t�F�N�g���
	int nAmount;		// �o����
	bool bUse;
}PARTICLE;

// �v���g�^�C�v�錾
void InitParticle(void);
void UpdateParticle(void);
void SetParticle(PARTICLE pati);

#endif // !_PARTICLE_H_
