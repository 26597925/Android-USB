
// LControllerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "LController.h"
#include "LControllerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLControllerDlg ��ȭ ����




CLControllerDlg::CLControllerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLControllerDlg::IDD, pParent)
	, str_loc(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STR_LOC, str_loc);
	DDX_Control(pDX, IDWCAM, mBtnCam);
}

BEGIN_MESSAGE_MAP(CLControllerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDWCAM, &CLControllerDlg::OnBnClickedWcam)
END_MESSAGE_MAP()


// CLControllerDlg �޽��� ó����

BOOL CLControllerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.
	//image = 0;
	image = (IplImage *)malloc(sizeof(IplImage));
	if(image==NULL) {
		AfxMessageBox(TEXT("�޸� �Ҵ� ����"));
		exit(1);
	}
	memset(image, 0x00, sizeof(image));
	image->roi = (struct _IplROI*)malloc(sizeof(struct _IplROI));
	if(image->roi==NULL) {
		AfxMessageBox(TEXT("�޸� �Ҵ� ����"));
		exit(1);
	}
	memset(image->roi, 0x00, sizeof(struct _IplROI));
	image->imageData = NULL;

	viewState = FALSE;
	OnBnClickedWcam();

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CLControllerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CLControllerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}



// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CLControllerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLControllerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString strLoc;
	strLoc.Format("X:%4d, Y:%4d", point.x, point.y);
	GetDlgItem(IDC_STR_LOC)->SetWindowText(_T(strLoc));
	//str_loc.SetString("111");
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CLControllerDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CLControllerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CLControllerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CLControllerDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CLControllerDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnRButtonUp(nFlags, point);
}

void CLControllerDlg::ShowIplImage(IplImage* piplimg, HDC hDCDst, RECT* pDstRect)
{
	if( pDstRect && piplimg && piplimg->depth == IPL_DEPTH_8U && piplimg->imageData )
    {
        uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
        BITMAPINFO* bmi = (BITMAPINFO*)buffer;
        int bmp_w = piplimg->width, bmp_h = piplimg->height;
 
        CvRect roi = cvGetImageROI( piplimg );
        CvRect dst = RectToCvRect( *pDstRect );
 
        if( roi.width == dst.width && roi.height == dst.height )
        {
            Show( piplimg, hDCDst, dst.x, dst.y, dst.width, dst.height, roi.x, roi.y );
        }
        else
        {
            SetStretchBltMode(hDCDst, (roi.width > dst.width) ? HALFTONE : COLORONCOLOR);
            FillBmpInfo(bmi, bmp_w, bmp_h, (piplimg->depth & 255) * piplimg->nChannels, piplimg->origin);
 
            ::StretchDIBits(hDCDst, dst.x, dst.y, dst.width, dst.height,
                roi.x, roi.y, roi.width, roi.height, piplimg->imageData, bmi, DIB_RGB_COLORS, SRCCOPY);
        }
	}
}

void CLControllerDlg::Show(IplImage* piplimg, HDC dc,
	int x, int y, int w, int h, int from_x, int from_y)
{
	if( piplimg && piplimg->depth == IPL_DEPTH_8U )
    {
        uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
        BITMAPINFO* bmi = (BITMAPINFO*)buffer;
        int bmp_w = piplimg->width, bmp_h = piplimg->height;
 
        FillBmpInfo( bmi, bmp_w, bmp_h, (piplimg->depth & 255) * piplimg->nChannels, piplimg->origin );
 
        from_x = MIN( MAX( from_x, 0 ), bmp_w - 1 );
        from_y = MIN( MAX( from_y, 0 ), bmp_h - 1 );
 
        int sw = MAX( MIN( bmp_w - from_x, w ), 0 );
        int sh = MAX( MIN( bmp_h - from_y, h ), 0 );
 
        SetDIBitsToDevice(
            dc, x, y, sw, sh, from_x, from_y, from_y, sh,
            piplimg->imageData + from_y * piplimg->widthStep,
            bmi, DIB_RGB_COLORS );
    }
}

void CLControllerDlg::FillBmpInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin)
{
	assert( bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));
 
    BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);
 
    memset( bmih, 0, sizeof(*bmih));
    bmih->biSize = sizeof(BITMAPINFOHEADER);
    bmih->biWidth = width;
    bmih->biHeight = origin ? abs(height) : -abs(height);
    bmih->biPlanes = 1;
    bmih->biBitCount = (unsigned short)bpp;
    bmih->biCompression = BI_RGB;
 
    if( bpp == 8 )
    {
        RGBQUAD* palette = bmi->bmiColors;
        int i;
        for( i = 0; i < 256; i++ )
        {
            palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
            palette[i].rgbReserved = 0;
        }
    }
}

void CLControllerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CWnd *pWnd = GetDlgItem(IDC_STATIC);
	CDC *pDc;

	if(1 == nIDEvent){
		if(send_msg("1")<0) {
			OnBnClickedWcam();
			AfxMessageBox(TEXT("������ ������ ������ϴ�."));
			return;
		}
		if(recv_msg()<0) {
			OnBnClickedWcam();
			AfxMessageBox(TEXT("������ ������ ������ϴ�."));
			return;
		}
		
		//cvGrabFrame(capture);
		//image = cvQueryFrame(capture);
		RECT rect;
		pWnd->GetClientRect(&rect);
		pDc = pWnd->GetDC();
		ShowIplImage(image, pDc->GetSafeHdc(), &rect);
	
		ReleaseDC(pDc);
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CLControllerDlg::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	//cvReleaseCapture(&capture);
	return CDialogEx::DestroyWindow();
}


void CLControllerDlg::OnBnClickedWcam()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(viewState == TRUE) {
		GetDlgItem(IDWCAM)->SetWindowText(_T("��"));
		//cvReleaseCapture(&capture);
		dataSocket.Close();
		viewState = FALSE;
		KillTimer(1);
	}
	else {
		// ���Ͽ��� or ��ġ�Է�
		//capture = cvCaptureFromCAM(0);

		// Odroid
		//m_strServerAddress = "192.168.0.22";
		// Nexus S
		m_strServerAddress = "192.168.0.29";
		if(dataSocket.m_hSocket != INVALID_SOCKET)
		{
			AfxMessageBox(TEXT("�̹� ������ ���� �Ǿ��ֽ��ϴ�."));
			return;
		}
		if(!dataSocket.Create())
		{
			AfxMessageBox(TEXT("���� ���� ����"));
			GetDlgItem(IDWCAM)->SetWindowText(_T("��"));
			return;
		}
		// IP�� ��Ʈ�� ���ῡ �����ϴ� ���
		if(!dataSocket.Connect(m_strServerAddress, PORT))
		{
			dataSocket.Close();
			AfxMessageBox(TEXT("���� ����"));
			GetDlgItem(IDWCAM)->SetWindowText(_T("��"));
			return;
		}
		/*
		if(!capture) {
			AfxMessageBox(TEXT("����� ��ķ��ġ�� �����ϴ�"));
			GetDlgItem(IDWCAM)->SetWindowText(_T("��"));
		}
		*/
		else {
		
			/* // �ػ󵵼���
			cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 200); 
			cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 400);
			*/

			// Ÿ�̸� �ӵ�����
			SetTimer(1,800,NULL);
			//SetTimer(1,((double)1/12)*1000,NULL);

			viewState = TRUE;
			//AfxMessageBox(TEXT("���� ����"));
			GetDlgItem(IDWCAM)->SetWindowText(_T("��"));
		}
	}
}
LRESULT CLControllerDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	char Rcvdata[MAXLINE];

	CDataSocket* pDataSocket = (CDataSocket*)wParam;

	pDataSocket->Receive(Rcvdata, sizeof(Rcvdata));

	CString strMsg = Rcvdata;

	if(!strcmp(strMsg, "2")){
		AfxMessageBox(TEXT(strMsg));
	}
	return 0;
}

// �������� ���� ���� ó��
LRESULT CLControllerDlg::OnCloseSocket(WPARAM wParam, LPARAM lParam)
{
	return 0;
}



int CLControllerDlg::recv_msg(void)
{
	int ret;
	BMPHEAD bh;
	int imgSize;
	char* pData = NULL;
	
	memset((void*)&bh, 0x00, sizeof(bh));
	ret = dataSocket.Receive(&bh, sizeof(bh), 0);
	if(ret<0) {
		return -1;
	}
	// BMPHEAD to IplImage
	image->nChannels = 3;
	image->depth = bh.bits / 3;
	image->origin = 0;
	image->width = bh.width;
	image->height = bh.depth; 
	image->roi->height = image->height;
	image->roi->width = image->width;

	imgSize = image->width * image->height
		* image->depth * image->nChannels / 8;
	if(image->imageData){
		realloc(image->imageData, imgSize);
	}
	else {
		image->imageData = (char*) malloc(imgSize);
	}
	if(!image->imageData)
		return -1;

	ret = 0;
	pData = image->imageData;
	do {
		ret = dataSocket.Receive(pData, imgSize, 0);
		if(ret<0) {
			return -1;
		}
		imgSize -= ret;
		pData += ret;
	}while(imgSize>0);

	/*
	image->nSize;                           
    image->ID;                                                     
    image->alphaChannel;                                    
    image->colorModel[4];             
    image->channelSeq[4];            
    image->dataOrder;                                                    
    image->align;        
    image->roi;                
    image->maskROI;    
    image->imageId;                    
    image->tileInfo;
    image->imageSize;    
    image->widthStep;                     
    image->BorderMode[4];
    image->BorderConst[4];
    image->imageDataOrigin;
	*/

	return 0;
}


void CLControllerDlg::inputDirectioinKey(int key)
{
	CString strCmd;
	switch(key){
	case INPUT_UP:
		strCmd.Format("%s", "\\\\CONTROL_U");
		break;
	case INPUT_DOWN:
		strCmd.Format("%s", "\\\\CONTROL_D");
		break;
	case INPUT_RIGHT:
		strCmd.Format("%s", "\\\\CONTROL_R");
		break;
	case INPUT_LEFT:
		strCmd.Format("%s", "\\\\CONTROL_L");
		break;
	case INPUT_ENTER:
		strCmd.Format("%s", "\\\\CONTROL_E");
		break;
	case INPUT_BACK:
		strCmd.Format("%s", "\\\\CONTROL_B");
		break;
	default:
		// no-effect
		break;
	}	

	sendMsg(strCmd);

	GetDlgItem(IDC_STR_LOC)->SetFocus();
	GetDlgItem(IDC_STR_LOC)->SendMessage(WM_KILLFOCUS, NULL); 	
}


BOOL CLControllerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	switch( pMsg->wParam ) {
		case VK_UP:
			inputDirectioinKey(INPUT_UP);
			break;
		case VK_DOWN:
			inputDirectioinKey(INPUT_DOWN);
			break;
		case VK_LEFT:
			inputDirectioinKey(INPUT_LEFT);
			break;
		case VK_RIGHT:
			inputDirectioinKey(INPUT_RIGHT);
			break;
		case VK_RETURN:
			inputDirectioinKey(INPUT_ENTER);
				return TRUE;
		case VK_ESCAPE:
			// �ڷΰ��� ��� ����
			inputDirectioinKey(INPUT_BACK);
			// ESCŰ�� ���� ���Ḧ �ϱ⶧���� �� ������ �������� retrun TRUE�� ����ߵ�
			return TRUE; 
		default:
			// no effect
			break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CLControllerDlg::sendMsg(CString strMsg)
{
	int ret = 0;
	ret = dataSocket.Send(AnsiToUTF8RetCString(strMsg), 
		AnsiToUTF8RetCString(strMsg).GetLength()+1);

	if(ret < 1){
		return;
	}
}


CString CLControllerDlg::AnsiToUTF8RetCString(CString inputStr)
{
	WCHAR szUnicode[MAXLINE];
	char szUTF8char[MAXLINE];

	CString strConvert;
	char* szSrc = (LPSTR)(LPCTSTR)inputStr;

	char szRetValue[MAXLINE] = "";

	int unicodeSize = MultiByteToWideChar(CP_ACP, 0,
		szSrc, (int)strlen(szSrc), 
		szUnicode, sizeof(szUnicode));

	int UTF8CodeSize = WideCharToMultiByte(CP_UTF8, 0, 
		szUnicode, unicodeSize, szUTF8char,
		sizeof(szUTF8char), NULL, NULL);

	memcpy(szRetValue, szUTF8char, UTF8CodeSize);
	strConvert = szRetValue;

	return strConvert;
}
