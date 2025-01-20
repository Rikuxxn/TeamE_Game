//=======================================
//
// ���[�V�����ǂݍ��ݏ���[motion.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "main.h"
#include "player.h"
#include "motion.h"
#include <stdio.h>
#include <string.h>
#include "enemy.h"

//=============================================
//�v���C���[�̃p�[�c�E���[�V�����ǂݍ��ݏ���
//=============================================
void LoadPlayerTEXT(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�t�@�C�����J��
	FILE* pFile = NULL;

	//�t�@�C�����J��
	pFile = fopen(MOTIONPATH_1, "r");

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nModel = 0;
	int nIdx = 0;
	int nCnt = 0;
	int nCntPos = 0;
	int nCntRot = 0;
	int nCntKey = 0;
	int nCntMotion = 0;

	Player* pPlayer = GetPlayer();

	if (pFile != NULL)
	{
		char aString[MAX_WORD];

		while (1)
		{
			// �ǂݔ�΂�
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "SCRIPT") == 0)
			{// SCRIPT��ǂݎ������

				while (1)
				{
					// �ǂݔ�΂�
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NUM_MODEL") == 0)
					{// NUM_MODEL��ǂݎ������
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// �l����
							fscanf(pFile, "%d", &nModel);
						}
					}
					else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
					{
						// MODEL_FILENAME��ǂݎ������
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// ���

							// �������ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							const char* MODEL_FILE = {};	// ���f���t�@�C�����i�[�p�̕ϐ�

							// �ǂݍ��񂾕������ۑ�����
							MODEL_FILE = aString;

							//X�t�@�C���̓ǂݍ���
							D3DXLoadMeshFromX(MODEL_FILE,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&pPlayer->motion.aModel[nCnt].pBuffMat,
								NULL,
								&pPlayer->motion.aModel[nCnt].dwNumMat,
								&pPlayer->motion.aModel[nCnt].pMesh);

							nCnt++; // nCnt���C���N�������g
						}
					}
					else if (strcmp(&aString[0], "CHARACTERSET") == 0)
					{
						while (1)
						{
							// �������ǂݔ�΂�
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "NUM_PARTS") == 0)
							{// NUM_PARTS��ǂݎ������

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{// �l����
									fscanf(pFile, "%d", &pPlayer->motion.nNumModel);
								}
							}
							else if (strcmp(&aString[0], "PARTSSET") == 0)
							{
								while (1)
								{
									// �������ǂݔ�΂�
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "INDEX") == 0)
									{// INDEX��ǂݎ������

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// ���
											fscanf(pFile, "%d", &nIdx);
										}
									}

									if (strcmp(&aString[0], "PARENT") == 0)
									{// PARENT��ǂݎ������

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// ���
											// �e
											fscanf(pFile, "%d", &pPlayer->motion.aModel[nIdx].nIdxModelParent);
										}
									}

									if (strcmp(&aString[0], "POS") == 0)
									{// INDEX��ǂݎ������

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// ���W����
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.z);
										}
									}

									if (strcmp(&aString[0], "ROT") == 0)
									{// INDEX��ǂݎ������

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// �p�x����
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.z);
										}
									}

									if (strcmp(&aString[0], "END_PARTSSET") == 0)
									{// END_PARTSSET��ǂݎ������
										// while�𔲂���
										break;
									}

								}// while����
							}
							else if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
							{
								break;
							}
						}//while����

					}
					else if (strcmp(&aString[0], "MOTIONSET") == 0)
					{

						while (1)
						{

							fscanf(pFile, "%s", &aString[0]);

							//if (strcmp(&aString[0], "LOOP") == 0)
							//{// NUM_PARTS��ǂݎ������

							//	fscanf(pFile, "%s", &aString[0]);
							
							//	if (strcmp(&aString[0], "=") == 0)
							//	{// �l����
							//		fscanf(pFile, "%d", &pPlayer->bLoopMotion);
							//	}
							//}
							if (strcmp(&aString[0], "NUM_KEY") == 0)
							{// NUM_PARTS��ǂݎ������

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{// �l����
									fscanf(pFile, "%d", &pPlayer->motion.aMotionInfo[nCntMotion].nNumKey);
								}

								while (nCntKey < pPlayer->motion.aMotionInfo[nCntMotion].nNumKey)
								{

									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "KEYSET") == 0)
									{
										while(1)
										{
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(&aString[0], "FRAME") == 0)
											{// NUM_PARTS��ǂݎ������
												fscanf(pFile, "%s", &aString[0]);

												if (strcmp(&aString[0], "=") == 0)
												{// �l����
													fscanf(pFile, "%d", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
													break;
												}
											}

										}

										while (1)
										{
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(&aString[0], "KEY") == 0)
											{

												while (1)
												{
													fscanf(pFile, "%s", &aString[0]);

													if (strcmp(&aString[0], "POS") == 0)
													{

														fscanf(pFile, "%s", &aString[0]);

														if (strcmp(&aString[0], "=") == 0)
														{// �l����
															fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPos].fPosX);
															fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPos].fPosY);
															fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPos].fPosZ);
															nCntPos++;
														}

													}
													if (strcmp(&aString[0], "ROT") == 0)
													{

														fscanf(pFile, "%s", &aString[0]);

														if (strcmp(&aString[0], "=") == 0)
														{// �l����
															fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotX);
															fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotY);
															fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotZ);
															nCntRot++;
														}

													}

													if (strcmp(&aString[0], "END_KEY") == 0)
													{
														break;
													}

												}//while����

											}

											if (strcmp(&aString[0], "END_KEYSET") == 0)
											{
												nCntKey++;
												nCntPos = 0;
												nCntRot = 0;
												break;
											}


										}

									}


								}//while����


							}

							if (strcmp(&aString[0], "END_MOTIONSET") == 0)
							{
								nCntKey = 0;
								nCntMotion++;
								break;
							}

						}//while����
					}

					if (strcmp(&aString[0], "END_SCRIPT") == 0)
					{

						// �t�@�C�������
						fclose(pFile);
						break;

					}

				}// while����

				break;
			}

		}// while����
	}

}
//=============================================
//�G�̃p�[�c�E���[�V�����ǂݍ��ݏ���
//=============================================
void LoadEnemyTEXT(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�t�@�C�����J��
	FILE* pFile = NULL;

	//�t�@�C�����J��
	pFile = fopen(MOTIONPATH_2, "r");

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nModel = 0;
	int nIdx = 0;
	int nCnt = 0;
	int nCntPos = 0;
	int nCntRot = 0;
	int nCntKey = 0;
	int nCntMotion = 0;

	Enemy* pEnemy = GetEnemy();

	if (pFile != NULL)
	{

		char aString[MAX_WORD];

		while (1)
		{
			// �ǂݔ�΂�
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "SCRIPT") == 0)
			{// SCRIPT��ǂݎ������

				while (1)
				{
					// �ǂݔ�΂�
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NUM_MODEL") == 0)
					{// NUM_MODEL��ǂݎ������
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// �l����
							fscanf(pFile, "%d", &nModel);
						}
					}
					else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
					{
						// MODEL_FILENAME��ǂݎ������
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// ���

							// �������ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							const char* MODEL_FILE = {};	// ���f���t�@�C�����i�[�p�̕ϐ�

							// �ǂݍ��񂾕������ۑ�����
							MODEL_FILE = aString;

							//X�t�@�C���̓ǂݍ���
							D3DXLoadMeshFromX(MODEL_FILE,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&pEnemy->motion.aModel[nCnt].pBuffMat,
								NULL,
								&pEnemy->motion.aModel[nCnt].dwNumMat,
								&pEnemy->motion.aModel[nCnt].pMesh);

							nCnt++; // nCnt���C���N�������g
						}
					}
					else if (strcmp(&aString[0], "CHARACTERSET") == 0)
					{
						while (1)
						{
							// �������ǂݔ�΂�
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "NUM_PARTS") == 0)
							{// NUM_PARTS��ǂݎ������

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{// �l����
									fscanf(pFile, "%d", &pEnemy->motion.nNumModel);
								}
							}
							else if (strcmp(&aString[0], "PARTSSET") == 0)
							{
								while (1)
								{
									// �������ǂݔ�΂�
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "INDEX") == 0)
									{// INDEX��ǂݎ������

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// ���
											fscanf(pFile, "%d", &nIdx);
										}
									}

									if (strcmp(&aString[0], "PARENT") == 0)
									{// PARENT��ǂݎ������

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// ���
											// �e
											fscanf(pFile, "%d", &pEnemy->motion.aModel[nIdx].nIdxModelParent);
										}
									}


									if (strcmp(&aString[0], "POS") == 0)
									{// INDEX��ǂݎ������

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// ���W����
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].pos.z);
										}
									}

									if (strcmp(&aString[0], "ROT") == 0)
									{// INDEX��ǂݎ������

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// �p�x����
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].rot.z);
										}
									}

									if (strcmp(&aString[0], "END_PARTSSET") == 0)
									{// END_PARTSSET��ǂݎ������
										// while�𔲂���
										break;
									}

								}// while����
							}
							else if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
							{
								break;
							}
						}//while����

					}
					else if (strcmp(&aString[0], "MOTIONSET") == 0)
					{

						while (1)
						{

							fscanf(pFile, "%s", &aString[0]);

							//if (strcmp(&aString[0], "LOOP") == 0)
							//{// NUM_PARTS��ǂݎ������

							//	fscanf(pFile, "%s", &aString[0]);

							//	if (strcmp(&aString[0], "=") == 0)
							//	{// �l����
							//		fscanf(pFile, "%d", &pPlayer->bLoopMotion);
							//	}
							//}
							if (strcmp(&aString[0], "NUM_KEY") == 0)
							{// NUM_PARTS��ǂݎ������

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{// �l����
									fscanf(pFile, "%d", &pEnemy->motion.aMotionInfo[nCntMotion].nNumKey);
								}

								while (nCntKey < pEnemy->motion.aMotionInfo[nCntMotion].nNumKey)
								{

									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "KEYSET") == 0)
									{

										while (1)
										{

											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(&aString[0], "FRAME") == 0)
											{// NUM_PARTS��ǂݎ������
												fscanf(pFile, "%s", &aString[0]);

												if (strcmp(&aString[0], "=") == 0)
												{// �l����
													fscanf(pFile, "%d", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
													break;
												}
											}

										}

										while (1)
										{
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(&aString[0], "KEY") == 0)
											{

												while (1)
												{
													fscanf(pFile, "%s", &aString[0]);

													if (strcmp(&aString[0], "POS") == 0)
													{

														fscanf(pFile, "%s", &aString[0]);

														if (strcmp(&aString[0], "=") == 0)
														{// �l����
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPos].fPosX);
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPos].fPosY);
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPos].fPosZ);
															nCntPos++;
														}

													}
													if (strcmp(&aString[0], "ROT") == 0)
													{

														fscanf(pFile, "%s", &aString[0]);

														if (strcmp(&aString[0], "=") == 0)
														{// �l����
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotX);
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotY);
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotZ);
															nCntRot++;
														}

													}

													if (strcmp(&aString[0], "END_KEY") == 0)
													{
														//nCntParts++;//���ӁI�I�I�I
														break;
													}

												}//while����

											}

											if (strcmp(&aString[0], "END_KEYSET") == 0)
											{
												nCntKey++;
												nCntPos = 0;
												nCntRot = 0;
												break;
											}


										}

									}


								}//while����


							}

							if (strcmp(&aString[0], "END_MOTIONSET") == 0)
							{
								nCntKey = 0;
								nCntMotion++;
								break;
							}

						}//while����
					}

					if (strcmp(&aString[0], "END_SCRIPT") == 0)
					{

						// �t�@�C�������
						fclose(pFile);
						break;

					}

				}// while����

				break;
			}

		}// while����
	}

}
