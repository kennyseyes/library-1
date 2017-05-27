#ifndef UTF8_INTO_GB2132
#define UTF8_INTO_GB2132
#include <QTextCodec>
void utf8ToGb2312(std::string& strUtf8)
{
QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

QString strUnicode= utf8Codec->toUnicode(strUtf8.c_str());
QByteArray ByteGb2312= gb2312Codec->fromUnicode(strUnicode);

strUtf8= ByteGb2312.data();
}
void gb2312ToUtf8(std::string& strGb2312)
{

QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

QString strUnicode= gb2312Codec->toUnicode(strGb2312.c_str());
QByteArray ByteUtf8= utf8Codec->fromUnicode(strUnicode);

strGb2312= ByteUtf8.data();
}
#endif // UTF8_INTO_GB2132

