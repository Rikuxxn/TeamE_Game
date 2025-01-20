//=======================================
//
// モーション読み込み処理[motion.cpp]
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
//プレイヤーのパーツ・モーション読み込み処理
//=============================================
void LoadPlayerTEXT(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//ファイルを開く
	FILE* pFile = NULL;

	//ファイルを開く
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
			// 読み飛ばし
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "SCRIPT") == 0)
			{// SCRIPTを読み取ったら

				while (1)
				{
					// 読み飛ばし
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NUM_MODEL") == 0)
					{// NUM_MODELを読み取ったら
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// 値を代入
							fscanf(pFile, "%d", &nModel);
						}
					}
					else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
					{
						// MODEL_FILENAMEを読み取ったら
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// 代入

							// 文字列を読み込む
							fscanf(pFile, "%s", &aString[0]);

							const char* MODEL_FILE = {};	// モデルファイル名格納用の変数

							// 読み込んだ文字列を保存する
							MODEL_FILE = aString;

							//Xファイルの読み込み
							D3DXLoadMeshFromX(MODEL_FILE,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&pPlayer->motion.aModel[nCnt].pBuffMat,
								NULL,
								&pPlayer->motion.aModel[nCnt].dwNumMat,
								&pPlayer->motion.aModel[nCnt].pMesh);

							nCnt++; // nCntをインクリメント
						}
					}
					else if (strcmp(&aString[0], "CHARACTERSET") == 0)
					{
						while (1)
						{
							// 文字列を読み飛ばす
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "NUM_PARTS") == 0)
							{// NUM_PARTSを読み取ったら

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{// 値を代入
									fscanf(pFile, "%d", &pPlayer->motion.nNumModel);
								}
							}
							else if (strcmp(&aString[0], "PARTSSET") == 0)
							{
								while (1)
								{
									// 文字列を読み飛ばす
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "INDEX") == 0)
									{// INDEXを読み取ったら

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 代入
											fscanf(pFile, "%d", &nIdx);
										}
									}

									if (strcmp(&aString[0], "PARENT") == 0)
									{// PARENTを読み取ったら

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 代入
											// 親
											fscanf(pFile, "%d", &pPlayer->motion.aModel[nIdx].nIdxModelParent);
										}
									}

									if (strcmp(&aString[0], "POS") == 0)
									{// INDEXを読み取ったら

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 座標を代入
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.z);
										}
									}

									if (strcmp(&aString[0], "ROT") == 0)
									{// INDEXを読み取ったら

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 角度を代入
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.z);
										}
									}

									if (strcmp(&aString[0], "END_PARTSSET") == 0)
									{// END_PARTSSETを読み取ったら
										// whileを抜ける
										break;
									}

								}// while文末
							}
							else if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
							{
								break;
							}
						}//while文末

					}
					else if (strcmp(&aString[0], "MOTIONSET") == 0)
					{

						while (1)
						{

							fscanf(pFile, "%s", &aString[0]);

							//if (strcmp(&aString[0], "LOOP") == 0)
							//{// NUM_PARTSを読み取ったら

							//	fscanf(pFile, "%s", &aString[0]);
							
							//	if (strcmp(&aString[0], "=") == 0)
							//	{// 値を代入
							//		fscanf(pFile, "%d", &pPlayer->bLoopMotion);
							//	}
							//}
							if (strcmp(&aString[0], "NUM_KEY") == 0)
							{// NUM_PARTSを読み取ったら

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{// 値を代入
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
											{// NUM_PARTSを読み取ったら
												fscanf(pFile, "%s", &aString[0]);

												if (strcmp(&aString[0], "=") == 0)
												{// 値を代入
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
														{// 値を代入
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
														{// 値を代入
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

												}//while文末

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


								}//while文末


							}

							if (strcmp(&aString[0], "END_MOTIONSET") == 0)
							{
								nCntKey = 0;
								nCntMotion++;
								break;
							}

						}//while文末
					}

					if (strcmp(&aString[0], "END_SCRIPT") == 0)
					{

						// ファイルを閉じる
						fclose(pFile);
						break;

					}

				}// while文末

				break;
			}

		}// while文末
	}

}
//=============================================
//敵のパーツ・モーション読み込み処理
//=============================================
void LoadEnemyTEXT(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//ファイルを開く
	FILE* pFile = NULL;

	//ファイルを開く
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
			// 読み飛ばし
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "SCRIPT") == 0)
			{// SCRIPTを読み取ったら

				while (1)
				{
					// 読み飛ばし
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NUM_MODEL") == 0)
					{// NUM_MODELを読み取ったら
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// 値を代入
							fscanf(pFile, "%d", &nModel);
						}
					}
					else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
					{
						// MODEL_FILENAMEを読み取ったら
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// 代入

							// 文字列を読み込む
							fscanf(pFile, "%s", &aString[0]);

							const char* MODEL_FILE = {};	// モデルファイル名格納用の変数

							// 読み込んだ文字列を保存する
							MODEL_FILE = aString;

							//Xファイルの読み込み
							D3DXLoadMeshFromX(MODEL_FILE,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&pEnemy->motion.aModel[nCnt].pBuffMat,
								NULL,
								&pEnemy->motion.aModel[nCnt].dwNumMat,
								&pEnemy->motion.aModel[nCnt].pMesh);

							nCnt++; // nCntをインクリメント
						}
					}
					else if (strcmp(&aString[0], "CHARACTERSET") == 0)
					{
						while (1)
						{
							// 文字列を読み飛ばす
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "NUM_PARTS") == 0)
							{// NUM_PARTSを読み取ったら

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{// 値を代入
									fscanf(pFile, "%d", &pEnemy->motion.nNumModel);
								}
							}
							else if (strcmp(&aString[0], "PARTSSET") == 0)
							{
								while (1)
								{
									// 文字列を読み飛ばす
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "INDEX") == 0)
									{// INDEXを読み取ったら

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 代入
											fscanf(pFile, "%d", &nIdx);
										}
									}

									if (strcmp(&aString[0], "PARENT") == 0)
									{// PARENTを読み取ったら

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 代入
											// 親
											fscanf(pFile, "%d", &pEnemy->motion.aModel[nIdx].nIdxModelParent);
										}
									}


									if (strcmp(&aString[0], "POS") == 0)
									{// INDEXを読み取ったら

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 座標を代入
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].pos.z);
										}
									}

									if (strcmp(&aString[0], "ROT") == 0)
									{// INDEXを読み取ったら

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 角度を代入
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &pEnemy->motion.aModel[nIdx].rot.z);
										}
									}

									if (strcmp(&aString[0], "END_PARTSSET") == 0)
									{// END_PARTSSETを読み取ったら
										// whileを抜ける
										break;
									}

								}// while文末
							}
							else if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
							{
								break;
							}
						}//while文末

					}
					else if (strcmp(&aString[0], "MOTIONSET") == 0)
					{

						while (1)
						{

							fscanf(pFile, "%s", &aString[0]);

							//if (strcmp(&aString[0], "LOOP") == 0)
							//{// NUM_PARTSを読み取ったら

							//	fscanf(pFile, "%s", &aString[0]);

							//	if (strcmp(&aString[0], "=") == 0)
							//	{// 値を代入
							//		fscanf(pFile, "%d", &pPlayer->bLoopMotion);
							//	}
							//}
							if (strcmp(&aString[0], "NUM_KEY") == 0)
							{// NUM_PARTSを読み取ったら

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{// 値を代入
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
											{// NUM_PARTSを読み取ったら
												fscanf(pFile, "%s", &aString[0]);

												if (strcmp(&aString[0], "=") == 0)
												{// 値を代入
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
														{// 値を代入
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
														{// 値を代入
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotX);
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotY);
															fscanf(pFile, "%f", &pEnemy->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntRot].fRotZ);
															nCntRot++;
														}

													}

													if (strcmp(&aString[0], "END_KEY") == 0)
													{
														//nCntParts++;//注意！！！！
														break;
													}

												}//while文末

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


								}//while文末


							}

							if (strcmp(&aString[0], "END_MOTIONSET") == 0)
							{
								nCntKey = 0;
								nCntMotion++;
								break;
							}

						}//while文末
					}

					if (strcmp(&aString[0], "END_SCRIPT") == 0)
					{

						// ファイルを閉じる
						fclose(pFile);
						break;

					}

				}// while文末

				break;
			}

		}// while文末
	}

}
