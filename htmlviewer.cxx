#include "htmlviewer.hxx"

HTMLViewer::HTMLViewer(QWidget* p)
    : QTextEdit(p)
{
    setReadOnly(true);
}

