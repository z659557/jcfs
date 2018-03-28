#pragma once

#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

// 2012.4.16 modify 

class CGifImage
{
public:
	CGifImage(void);
	~CGifImage(void);

public:
	BOOL LoadFromFile(LPCTSTR pszFileName);
	BOOL LoadFromIStream(IStream* pStream);
	BOOL LoadFromBuffer(const BYTE* lpBuf, DWORD dwSize);
	BOOL LoadFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszResType);
	BOOL LoadFromResource(HINSTANCE hInstance, UINT nIDResource, LPCTSTR pszResType);
	BOOL SaveAsFile(LPCTSTR pszFileName);
	void Destroy();
	BOOL IsAnimatedGif();
	UINT GetFrameCount();
	long GetFrameDelay(int nFramePos = -1);
	void ActiveNextFrame();
	void SelectActiveFrame(int nFramePos);
	BOOL Draw(HDC hDestDC, int xDest, int yDest, int nFramePos = -1);
	BOOL Draw(HDC hDestDC, const RECT& rectDest, int nFramePos = -1);
	int GetWidth() const;
	int GetHeight() const;
	UINT GetCurFramePos();
	BOOL GetRawFormat(GUID * lpGuid);

private:
	CLSID GetEncoderClsidByExtension(const WCHAR * lpExtension);
	BOOL ReadGifInfo();

private:
	Gdiplus::Image* m_pImage;		// ͼƬ����ָ��
	UINT m_nFrameCnt;				// GIF������֡��
	UINT m_nFramePos;				// ��ǰ֡
	long *m_pFrameDelay;			// ÿ֡�л���ʱʱ��
};