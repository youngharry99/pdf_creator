#include <stdio.h>
#include <hpdf.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define FONT_PATH "fonts/ArialUnicodeMS.ttf"

void error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%d\n",
      (unsigned int) error_no, (int) detail_no);
    //throw std::exception (); /* throw exception on error */
}

int main()
{
    int fd = open("fonts/ArialUnicodeMS.ttf", O_RDONLY);
    printf ("fd:%d\n", fd);
    if (fd == -1)
    {
        perror("Failed to open font file");
        
    }
    close(fd);
    
    //HPDF_Font font;
    HPDF_Page page_1;
    const char* text = "You Know M32222";

    // 创建新的PDF文档对象
    HPDF_Doc pdf = HPDF_New(error_handler, NULL);
    if (!pdf) {
    printf ("Error: cannot create pdf object.\n");
    return -1;
    }

    // 使用UTF-8编码
    HPDF_UseUTFEncodings(pdf);
    HPDF_SetCurrentEncoder(pdf, "UTF-8");

    // 2.1 创建一个 Arial Unicode MS 字体对象
    const char* font_name = HPDF_LoadTTFontFromFile(pdf, FONT_PATH, HPDF_FALSE);
    // 创建一个字体对象
    HPDF_Font font = HPDF_GetFont(pdf, font_name, "UTF-8");
    if (!font) {
        printf("Error: Unable to create font\n");
        HPDF_Free(pdf);
        return EXIT_FAILURE;
    }

    // 1.1向文档中添加一页
    page_1 = HPDF_AddPage(pdf);
    if (!page_1) {
        printf("Error: Unable to create PDF page\n");
        HPDF_Free(pdf);
        return -1;
    }

    // 1.2 设置 page_1 尺寸为 A4
    HPDF_Page_SetSize(page_1, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    
    // 2.2 设置页面上绘制文本所使用的字体和字体大小
    HPDF_Page_SetFontAndSize(page_1, font, 12);

    // 3.1 在页面上绘制文字
    HPDF_Page_BeginText(page_1);
    HPDF_Page_MoveTextPos(page_1, 50, HPDF_Page_GetHeight(page_1) - 50);
    HPDF_Page_ShowText(page_1, text);
    HPDF_Page_EndText(page_1);

    // 4.1 保存 PDF 文件
    if (HPDF_SaveToFile(pdf, "result.pdf") != HPDF_OK) {
        printf("Error: Unable to save PDF file\n");
        HPDF_Free(pdf);
        return -1;
    }

    // 5.1 释放资源
    HPDF_Free(pdf);

    printf("PDF file created successfully\n");

    return 0;
}
