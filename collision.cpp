/*==============================================================================

   �e�N�X�`���̕`�� [collision.cpp]
                                                         Author :
                                                         Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "collision.h"

//*****************************************************************************
// �����蔻�菈��
//*****************************************************************************
void UpdateCollision()
{

}

//---------------------------------------------------------------------
// �~���m�̓����蔻��
// in pos1, pos2: �~�̒��S���W
//    size1, size2: �~�̔��a
// out true:������ flase:�O��
//---------------------------------------------------------------------
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
    //���S���m�̒���(���[�g���g���o�[�W����)
    D3DXVECTOR2 distance = pos1 - pos2;
    float length = D3DXVec2Length(&distance);

    //�~1�Ɖ~2�̔��a�̑��a
    float size = size1 + size2;

    //���S���m�̒����Ɣ��a�̑��a�̔�r
    if (length < size)
    {
        return true; //�~���m���������Ă���
    }

    return false; //�~���m���������Ă��Ȃ�
}

//---------------------------------------------------------------------
// �Z�`���m�̓����蔻��
// in pos1, pos2: ��`�̒��S���W
//    size1, size2: ��`�̃T�C�Y
// out true:������ flase:�O��
//---------------------------------------------------------------------
bool CollisionBB(float posX1, float posY1, float posX2, float posY2, float sizeX1, float sizeY1, float sizeX2, float sizeY2)
{
    D3DXVECTOR2 min1, max1; //�L�����N�^1�̍�����W�A�E�����W
    D3DXVECTOR2 min2, max2; //�L�����N�^2�̍�����W�A�E�����W

    min1.x = posX1 - sizeX1 * 0.5f;//�L�����N�^1�̍�����WX
    min1.y = posY1 - sizeY1 * 0.5f;//�L�����N�^1�̍�����WY
    max1.x = posX1 + sizeX1 * 0.5f;//�L�����N�^1�̉E�����WX
    max1.y = posY1 + sizeY1 * 0.5f;//�L�����N�^1�̉E�����WY

    min2.x = posX2 - sizeX2 * 0.5f;//�L�����N�^2�̍�����WX
    min2.y = posY2 - sizeY2 * 0.5f;//�L�����N�^2�̍�����WY
    max2.x = posX2 + sizeX2 * 0.5f;//�L�����N�^2�̉E�����WX
    max2.y = posY2 + sizeY2 * 0.5f;//�L�����N�^2�̉E�����WY

    //X���̔���
    if ((min1.x < max2.x) && (max1.x > min2.x))
    {
        //Y���̔���
        if ((min1.y < max2.y) && (max1.y > min2.y))
        {
            return true; //1�̋�`�͓������Ă���
        }
    }

    return false; //2�̒Z�a�͓������Ă��Ȃ�

}

//---------------------------------------------------------------------
// �Z�`���m����`�̓����蔻��(�p�x�t)
// in pos1, pos2: ��`�̒��S���W
// size1, size2: ��`�̃T�C�Y
// rot2: ��`�̊p�x(���W�A��)
// out true:������ flase:�O��
//---------------------------------------------------------------------
bool CollisionRot(float posX1, float posY1, float posX2, float posY2, float sizeX1, float sizeY1, float sizeX2, float sizeY2, float rot2)
{
    //�Q�l https://yttm-work.jp/collision/collision_0007.html
    // ��`�̒��S�����_�Ƃ������΍��W���쐬����
    D3DXVECTOR2 relative_position = D3DXVECTOR2(posX1 - posX2, posY1 - posY2);

    // ���΍��W�ɑ΂��ċ�`�̉�]��ł������t�s����|����
    D3DXVECTOR2 transform_pos = D3DXVECTOR2(
        cosf(rot2) * relative_position.x + sinf(rot2) * relative_position.y,
        -sinf(rot2) * relative_position.x + cosf(rot2) * relative_position.y
    );

    // ��`�Ɠ_�̓����蔻����s��
    if (-sizeX2 / 2.0f <= transform_pos.x + sizeX1 / 2.0f && sizeX2 / 2.0f >= transform_pos.x - sizeX1 / 2.0f &&
        -sizeY2 / 2.0f <= transform_pos.y + sizeY1 / 2.0f && sizeY2 / 2.0f >= transform_pos.y - sizeY1 / 2.0f)
    {
        return true;
    }

    return false;
}