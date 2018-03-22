
/*
	CCReuseVisibleScrollViewFacade
	������Ҫ���ش�����items��ScrollView���ù̶������Ŀɼ�items����ScrollView��������̬����Itemsģ������˴���items
	��Ϊ��ҵ���߼������ǿ��ֻ�ṩ����һ��ScrollViewʵ���İ�װ����ɹ��ܣ�����ֱ�Ӽ̳�ScrollView
	ֻ֧�ֵ�����kCCScrollViewDirectionHorizontal��kCCScrollViewDirectionVertical
*/

#ifndef __CCREVISCROLLVIEWFACADE_H__
#define __CCREVISCROLLVIEWFACADE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

	//class cocos2d::CCPoint;
	//class cocos2d::CCObject;
	//class cocos2d::CCArray;
	//class cocos2d::CCNode;

NS_CC_EXT_BEGIN
	class CCScrollView;
	class CCScrollViewDelegate;
	class CCReViScrollViewFacade;
	//
	class CCReViSvItemData : public CCObject	//Model
	{
		friend class CCReViScrollViewFacade;
	public:
		CCReViSvItemData()
			:m_iIdx(0),m_iItemNodeIdx(-1)
		{
			m_ptPosition.x = m_ptPosition.y = 0.f;
		}
	public:
		CCPoint		m_ptPosition;
		//CCSize		m_szContentSize;
		unsigned int	m_iIdx;	//for debug
	private:
		unsigned int	m_iItemNodeIdx;
	};
	//
	class CCReViSvItemNodeFacade/* : virtual public CCObject*/	//View
	{
		friend class CCReViScrollViewFacade;
	public:
		virtual ~CCReViSvItemNodeFacade(){};
		virtual void initItemView() = 0;
		virtual void refreshItemView(CCReViSvItemData* pItem) = 0;
	protected:
		CCNode*		m_pItemNode;
	};
	//
#define Macro_FixedViewItemsMaxNum 4
#define Macro_FixedItemViewsMultiply 3
	//
	class CCReViScrollViewFacade : CCScrollViewDelegate //Control
	{
	public:
		CCReViScrollViewFacade(CCScrollView* pView);
		virtual ~CCReViScrollViewFacade();

		/*
			iNum:�ܿص�itemviews�Ķ�̬���򣬵ȷ�ΪMacro_FixedItemViewsMultiply���֣�ÿ����iNum��itemviews
			iSize:��ʼ����ʱ��Ԥ���¿����ж����ܿ�itemviews
		*/
		bool	init(unsigned int iNum = Macro_FixedViewItemsMaxNum, 
			unsigned int iSize = Macro_FixedViewItemsMaxNum, CCScrollViewDelegate* pOtherDelegate = NULL,unsigned int lineNum = 1);

		unsigned int getMaxDynamicControledItemViewsNum()
		{
			return m_iFixedViewItemsMaxNum*Macro_FixedItemViewsMultiply;
		}

	//
	public:
		virtual void scrollViewDidScroll(CCScrollView* view);
		virtual void scrollViewDidZoom(CCScrollView* view)
		{
			if (m_pOtherDelegate)
				m_pOtherDelegate->scrollViewDidZoom(view);
			//����������˵��С�Զ����ظ���items���Ŵ��Զ��ͷŹ���items
		}
		virtual void scrollViewDidDeaccelerateScrolling(CCScrollView* view, CCPoint initSpeed)
		{
			if (m_pOtherDelegate)
				m_pOtherDelegate->scrollViewDidDeaccelerateScrolling(view, initSpeed);
		}
		virtual void scrollViewDidDeaccelerateStop(CCScrollView* view, CCPoint initSpeed)
		{
			if (m_pOtherDelegate)
				m_pOtherDelegate->scrollViewDidDeaccelerateStop(view, initSpeed);
		}

	//
	public:
		void	addItem(CCReViSvItemData* item, CCReViSvItemNodeFacade* node = NULL);
		void	insertItemAtIdx(CCReViSvItemData* item, int idx, CCReViSvItemNodeFacade* node = NULL);
		void	removeItem(CCReViSvItemData* item);
		void	removeItemAtIdx(int idx);
		void	clearAllItems();

		//add by zhenhui
		//Hint:
		//1.)���ڵ�����ˢ��scroolview�е����ݣ�������Ҫ����rebuildAll,�ұ��ֵ�ǰλ�ã����̵깺����Ʒ��ˢ��scrollView�ȡ�
		//2.)����������ĳ��content����Ҫɾ����content�����������Ҫrebuild������getContainer()->setPosition()����������setContentOffset������scrollViewDidScroll�����´�λ
		void	refreshDynamicScrollView();
		//end 
		/*
			��̬����λ�ø��õ�items����ʼλ�ã��ⲿ��items�������������еģ������ⲿ����������items���ܱ�FacadeӰ��
			addItem�ڲ�δ�Զ�����λ�ã�ȫ��addItem��Ϻ�Ҫ����������е���ScrollView��contentsize��offset�����룩
			�ٵ��ñ���������̬����λ�û��ں����������ܿ�items�����Զ�����
			�������ܿ�items�����ϣ�Ҫ�������ָ����һ��λ��&�������ܿ�item��Ϊê��(0.0f, 0.0f)�ο������룩
			��������ScrollViewû������items��ָ����һ���ܿ�item��ʼ��ʾ��ViewRect�����Ͻ�
		*/
		void	setDynamicItemsStartPosition(unsigned int idx);
		unsigned int getStartPosition() { return m_iCurStartIdx; };
		/*
			���ItemData��Ӧ��ItemNode��ǰ��סrealloaded
		*/
		CCReViSvItemNodeFacade* findItemNodeByItemData(CCReViSvItemData* pItem);

		CCReViSvItemNodeFacade* findItemNodeByIndex(unsigned int index);
	//
	private:
		void	loadDownOrLeftAndRefresh();
		void	loadUpOrRightAndRefresh();

	//
	private:
		CCScrollView*	m_pScrollView;
		/*
			
		*/
		CCScrollViewDelegate*	m_pOtherDelegate;
		/*
			ScrollView�ɼ������ں���Items�������ڲ�������Macro_FixedItemViewsMultiply������Items��ʵ�ֶ�̬����ģ�����Items
		*/
		unsigned int	m_iFixedViewItemsMaxNum;
		/*
		ÿ��item�ĸ���
		*/
		unsigned int	mLineNum;
		/*
		*/
		CCArray*		m_arrayItems;
		/*
			ScrollView�ɼ��������ϻ�����ǰ����ʾ��Item��m_arrayItems�е�����
		*/
		unsigned int	m_iCurStartIdx;
		/*
		*/
		//CCArray*		m_arrayItemViews;
		typedef std::vector<CCReViSvItemNodeFacade*> ArrayItemViewVec;
		ArrayItemViewVec m_arrayItemViews;
		/*
		*/
		CCPoint			m_ptCurStart;
		/*
			�ܿص�itemviews�Ķ�̬���򣬵ȷ�ΪMacro_FixedItemViewsMultiply���֣�ÿ����m_iFixedViewItemsMaxNum��itemviews
			ȡֵ[0,(Macro_FixedItemViewsMultiply-1)]����ʾ��ǰ��Ӧ��m_iCurStartIdx�Ĳ���
		*/
		unsigned int	m_iVirtualPartRectIdx;
		/*
		*/
		unsigned int	m_iRealLoadedStartIdx;
		unsigned int	m_iRealLoadedEndIdx;
	};


NS_CC_EXT_END

#endif//__CCREVISCROLLVIEWFACADE_H__


