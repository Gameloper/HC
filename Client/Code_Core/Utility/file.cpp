#include "file.h"


#include <iostream>
#include <string>

int  PathExist(char *strPath)
{
	return (access(strPath, 0) == 0); 
}
int CreateMultDir(const char *dir)
{
	char *tarDir;  /* ·������ */
	int  dirLen;  /* ·������ */
	char *szTemp;  /* ����·������ʱ���� */
	char *pTmp;  /* ��ʱָ����� */

	dirLen = strlen(dir) + 1;
	tarDir = (char*)malloc(dirLen*sizeof(char));
	szTemp = (char*)malloc(dirLen*sizeof(char));
	sprintf(tarDir,dir);

	if(tarDir[dirLen-1]=='/')
	{
		tarDir[dirLen-1]='\0';    // ��ɾ�����ġ�/��
	}
	pTmp = tarDir;
	while (1)            // ֮���λ��(Ҫ�ܽ����ѭ��, �����Ƕ���Ŀ¼, ��: c:\һ��Ŀ¼\����Ŀ¼\...)
	{
		// ����·���ָ�����'\'
		pTmp = strchr(pTmp, '/'); // ��һ�εĳ���λ��(��ַ)
		if (NULL == pTmp)
		{
			break;
		}
		memset(szTemp,'\0',dirLen);
		strncpy(szTemp, tarDir, (pTmp-tarDir)/sizeof(char));     // ��: e:\1

		if (!PathExist(szTemp)) // ���������, ��һ·�����������ڶ���Ŀ¼
		{
			if (_mkdir(szTemp)) 
			{
				return 0;
			}
		}
		_chmod( szTemp, _S_IWRITE );
		pTmp ++;
	}
	if (!PathExist(tarDir)) // ���������, ��һ·�����������ڶ���Ŀ¼
	{
		if (_mkdir(tarDir)) 
		{
			return 0;
		}
	}
	free(tarDir);
	free(szTemp);
	return 1;
}

//�����ļ��к���
void TraverseFolder(const std::string& sourthPath,const std::string& subpath,std::vector<File_Struct>& pathMap,
	std::vector<std::string>& fileFliterVec,std::vector<std::string>& pathFliterVec)
{
	std::string rootpath = sourthPath;
	_finddata_t file;
	rootpath.append("/");
	rootpath.append(subpath);
	rootpath.append("/*.*");
	long lf;
	if((lf = _findfirst(rootpath.c_str(), &file)) == -1l)
	{
		std::cout << "Path: " + rootpath + "not found.\n";
	}
	else
	{
		while (_findnext( lf, &file) == 0)
		{
			if ((file.attrib & _A_SUBDIR))
			{
				if(strcmp(file.name,"..")!=0 && strcmp(file.name,".svn")!=0)
				{
					std::string fileName = file.name;
					bool isFliterPath = false;
					std::vector<std::string>::iterator iter = pathFliterVec.begin();
					for (; iter!= pathFliterVec.end();++iter)
					{
						if (*iter == fileName)
						{
							isFliterPath = true;
							break;
						}
					}
					if (!isFliterPath)
					{
						std::string thesubpath = subpath+"/"+file.name;
						TraverseFolder(sourthPath,thesubpath,pathMap,fileFliterVec,pathFliterVec);
					}
				}
			}
			else
			{
				std::string fileName = file.name;
				bool isContain = false;
				std::string::size_type dotPos = fileName.find_last_of(".");
				std::string suffixStr;
				if (dotPos == std::string::npos)
				{
					suffixStr = "";
				}
				else
				{
					suffixStr = fileName.substr(dotPos,fileName.length());
				}
				std::vector<std::string>::iterator iter = fileFliterVec.begin();
				if (fileFliterVec.size()!=0)
				{
					for (; iter!= fileFliterVec.end(); ++iter)
					{
						if (suffixStr == *iter)
						{
							isContain = true;
							break;
						}
					}
				}
				if (isContain)
				{
					std::string thefilePath = subpath+"/";
					thefilePath.append(fileName);

					File_Struct fileStr(fileName,thefilePath);
					pathMap.push_back(fileStr);
				}
			}
		}
	}
	_findclose(lf);
	//�����ļ���
	//	while (TRUE)
	//	{
	//		if (findFileData.cFileName[0] != _T('.'))
	//		{//���ǵ�ǰ·�����߸�Ŀ¼�Ŀ�ݷ�ʽ
	//
	//			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	//			{//����һ����ͨĿ¼
	//				//������һ����Ҫɨ����ļ���·��
	//				_tcscpy_s(szFind, MAX_PATH, sourPath);    
	//				_tcscat_s(szFind, _T("\\"));    
	//				_tcscat_s(szFind, findFileData.cFileName);
	//				///_tcscat_s(szNextDir, _T("\\*"));
	//				//������Ŀ¼
	//				TraverseFolder(szFind,pathMap,fliterVec);
	//			}
	//			else
	//			{
	//				//_tprintf(_T("%s\\%s\n"), lpPath, findFileData.cFileName);
	//				char szBuf[1000]; 
	//				WideCharToMultiByte(CP_ACP, 0, findFileData.cFileName, sizeof(findFileData.cFileName), szBuf, sizeof(szBuf), NULL, FALSE);
	//				std::string fileName = szBuf;
	//				std::string suffixStr = fileName.substr(fileName.find_last_of("."),fileName.length());
	//				std::vector<std::string>::iterator iter = fliterVec.begin();
	//				bool isContain = false;
	//				if (fliterVec.size()!=0)
	//				{
	//					for (; iter!= fliterVec.end(); ++iter)
	//					{
	//						if (suffixStr == *iter)
	//						{
	//							isContain = true;
	//							break;
	//						}
	//					}
	//				}
	//				else
	//				{
	//					isContain = true;
	//				}
	//				if(isContain)
	//				{
	//					std::wstring path = sourPath;
	//					std::string filePath = std::string(path.begin(),path.end());
	//					File_Struct file(fileName,filePath);
	//					std::cout << filePath + "\\" + fileName << std::endl;
	//					pathMap.push_back(file);
	//				}
	//			}
	//		}
	//		//����ǵ�ǰ·�����߸�Ŀ¼�Ŀ�ݷ�ʽ����������ͨĿ¼����Ѱ����һ��Ŀ¼�����ļ�
	//		bRet = ::FindNextFile(hFind, &findFileData);
	//		if (!bRet)
	//		{
	//			break;
	//		}
	//	}
	//	::FindClose(hFind);
}
