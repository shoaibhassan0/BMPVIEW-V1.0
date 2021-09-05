/*
	Batkit: Bmpviewer on console....

	Copyright (c) 2021 shoaib hassan.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>
	
	
	
	
	
Contributions:

Steffen Ilhardt: original insertbmp function.
*/




#include <windows.h>
int previewBmp(char *szBmpPath, long x, long y, long z, long w, long h, DWORD dwRop)
{
	HWND hWnd = NULL;
	HDC hDc = NULL, hDcBmp = NULL;
	HBITMAP hBmp1 = NULL, hBmp2 = NULL;
	HGDIOBJ hGdiObj = NULL;
	BITMAP bmp = {0};
	int iRet = EXIT_FAILURE;

	if ((hWnd = GetConsoleWindow()))
	{
		if ((hDc = GetDC(hWnd)))
		{
			if ((hDcBmp = CreateCompatibleDC(hDc)))
			{
				if ((hBmp1 = (HBITMAP)LoadImage(NULL, szBmpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)))
				{
					if (GetObject(hBmp1, sizeof(bmp), &bmp))
					{
						if (w == -1) {
							if ((w = bmp.bmWidth * z / 100.0 + 0.5) <= 0 || (h = bmp.bmHeight * z / 100.0 + 0.5) <= 0)
							{
								w = bmp.bmWidth;
								h = bmp.bmHeight;
							}
						} 
						if ((hBmp2 = (HBITMAP)CopyImage((HANDLE)hBmp1, IMAGE_BITMAP, w, h, LR_COPYDELETEORG)))
						{
							if ((hGdiObj = SelectObject(hDcBmp, hBmp2)) && hGdiObj != HGDI_ERROR)
							{
								if (BitBlt(hDc, (int)x, (int)y, (int)w, (int)h, hDcBmp, 0, 0, dwRop))
									iRet = EXIT_SUCCESS;
								DeleteObject(hGdiObj);
							}
							DeleteObject(hBmp2);
						}
					}
					DeleteObject(hBmp1);
				}
				ReleaseDC(hWnd, hDcBmp);
			}
			ReleaseDC(hWnd, hDc);
			ReleaseDC(hWnd, hDc);
		}
	}
	return iRet;
}
int main(int argc, char **argv) {
	if (argc < 2) return 0;
		
	DWORD bitOp[] = { SRCCOPY, SRCPAINT, SRCAND, SRCINVERT, SRCERASE, NOTSRCCOPY, NOTSRCERASE, MERGECOPY, MERGEPAINT, PATCOPY, PATPAINT, PATINVERT, DSTINVERT, BLACKNESS, WHITENESS, NOMIRRORBITMAP, CAPTUREBLT };
	char* bitOp_S[] = { "SRCCOPY", "SRCPAINT", "SRCAND", "SRCINVERT", "SRCERASE", "NOTSRCCOPY", "NOTSRCERASE", "MERGECOPY", "MERGEPAINT", "PATCOPY", "PATPAINT", "PATINVERT", "DSTINVERT", "BLACKNESS", "WHITENESS", "NOMIRRORBITMAP", "CAPTUREBLT" };
	DWORD selBitOp = SRCCOPY;
		
	int i, x,y,z = 100, w = -1, h = -1;
	
	x = atoi(argv[2]);
	y = atoi(argv[3]);
	
	if (argc > 4) z = atoi(argv[4]);
	if (argc > 5) { w = atoi(argv[4]); h = atoi(argv[5]); }

	if (previewBmp(argv[1], x, y, z, w, h, selBitOp) == EXIT_SUCCESS) ;
	return 0;
}
