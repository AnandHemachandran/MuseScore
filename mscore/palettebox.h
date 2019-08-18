//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2011-2016 Werner Schweer and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENSE.GPL
//=============================================================================

#ifndef __PALETTE_BOX_H__
#define __PALETTE_BOX_H__

#include "paletteBoxButton.h"
#include <QTreeWidget>


namespace Ms {

class XmlWriter;
class XmlReader;
class Palette;

//---------------------------------------------------------
//   PaletteBox
//---------------------------------------------------------
class PaletteTree : public QTreeWidget {
      Q_OBJECT

      protected:
         virtual void resizeEvent(QResizeEvent *event) override;
         virtual void showEvent(QShowEvent *event) override;
         virtual void contextMenuEvent(QContextMenuEvent*) override;

      private slots:
         void deleteTriggered(QTreeWidgetItem* item)     { emit paletteItemCmd(PaletteCommand::PDELETE, item);  }
         void saveTriggered(QTreeWidgetItem* item)       { emit paletteItemCmd(PaletteCommand::SAVE, item);    }
         void loadTriggered(QTreeWidgetItem* item)       { emit paletteItemCmd(PaletteCommand::LOAD, item);    }
         void propertiesTriggered(QTreeWidgetItem* item) { emit paletteItemCmd(PaletteCommand::EDIT, item);    }
         void upTriggered(QTreeWidgetItem* item)         { emit paletteItemCmd(PaletteCommand::UP, item);      }
         void downTriggered(QTreeWidgetItem* item)       { emit paletteItemCmd(PaletteCommand::DOWN, item);    }
         void newTriggered(QTreeWidgetItem* item)        { emit paletteItemCmd(PaletteCommand::NEW, item);     }
         void paletteItemCmd(PaletteCommand, QTreeWidgetItem*);

      public:
         PaletteTree(QWidget* parent);
   }; 


class PaletteBox : public QDockWidget {
      Q_OBJECT

      QVBoxLayout* vbox;
      Palette* newPalette(const QString& name, int slot);
      QComboBox* workspaceList;
      QLineEdit* _searchBox;
      PaletteTree* tree = nullptr;
      const int paletteStretch = 1000;
      //QAction* singlePaletteAction;
      QToolButton* addWorkspaceButton;
      bool keyboardNavigation = false;

   private slots:
      void paletteCmd(PaletteCommand, int);
      void closeAll();
      void workspaceSelected(int idx);
      void newWorkspaceClicked();
      void setSinglePalette(bool);
      void filterPalettes(const QString& text);

   signals:
      void changed();

   private:
      void changeEvent(QEvent *event);
      void retranslate();

   public:
      PaletteBox(QWidget* parent = 0);
      void addPalette(Palette*);
      void write(XmlWriter&);
      bool read(XmlReader&);
      void clear();
      QList<Palette*> palettes() const;
      void updateWorkspaces();
      QLineEdit* searchBox() { return _searchBox; }
      bool noSelection();
      void mousePressEvent(QMouseEvent* ev, Palette* p1);
      void navigation(QKeyEvent *event);
      bool eventFilter(QObject* obj, QEvent *event);
      void setKeyboardNavigation(bool val) { keyboardNavigation = val; }
      bool getKeyboardNavigation() { return keyboardNavigation; }
      void selectWorkspace(QString path);
      void selectWorkspace(int idx);
      };

//---------------------------------------------------------
//   PaletteBoxScrollArea
//---------------------------------------------------------

class PaletteBoxScrollArea : public QScrollArea {
       Q_OBJECT

    public:
      virtual QSize sizeHint() const;
      };

} // namespace Ms
#endif

