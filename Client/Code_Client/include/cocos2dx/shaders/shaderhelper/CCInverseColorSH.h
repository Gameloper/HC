#ifndef __CCBLURSCREEN_H__
#define __CCBLURSCREEN_H__

#include "CCShaderHelper.h"

NS_CC_BEGIN

//��Ҫ����� Shader Programʹ�� ���ṩ�ḻ��ʵ�Shader

class CCTexture2D;
class CCGLProgram;

class CC_DLL CCInverseColorSH : public CCShaderHelper
{
public:

	CCInverseColorSH(CCGLProgram* _program);

	virtual ~CCInverseColorSH();

	virtual void init();
	virtual void begin();
	virtual void end();

	void setInverseTexture(CCTexture2D* _tex);

protected:
	int s_Tex0;

protected:
	
	CCTexture2D* m_InverseTex;
};


NS_CC_END

#endif /* __CCBLURSCREEN_H__ */
