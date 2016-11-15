/***************************************************************
 * Name:      ToolKit3App.h
 * Purpose:   Defines Application Class
 * Author:    Christopher Plewright (chris@createng.com)
 * Created:   2016-10-08
 * Copyright: Christopher Plewright (www.createng.com)
 * License:
 **************************************************************/

#ifndef ToolKit3APP_H
#define ToolKit3APP_H

#include <wx/app.h>
#include "SettingsDAO.h"

class ToolKit3App : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // ToolKit3APP_H
