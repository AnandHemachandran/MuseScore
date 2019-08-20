//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2013 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __PALETTE_BOX_BUTTON_H__
#define __PALETTE_BOX_BUTTON_H__

namespace Ms {

class Palette;

enum class PaletteCommand : char {
      PDELETE,
      SAVE,
      LOAD,
      EDIT,
      UP,
      DOWN,
      NEW
      };

//---------------------------------------------------------
//   PaletteTree
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
//---------------------------------------------------------
//   PaletteBoxButton
//---------------------------------------------------------

class PaletteBoxButton : public QToolButton {
      Q_OBJECT

      Palette* palette;
      QAction* editAction;

      int id;

      virtual void changeEvent(QEvent*);
      virtual void paintEvent(QPaintEvent*);
      virtual void contextMenuEvent(QContextMenuEvent*);
      virtual QSize sizeHint() const;

   private slots:
      void deleteTriggered()     { emit paletteCmd(PaletteCommand::PDELETE, id);  }
      void saveTriggered()       { emit paletteCmd(PaletteCommand::SAVE, id);    }
      void loadTriggered()       { emit paletteCmd(PaletteCommand::LOAD, id);    }
      void propertiesTriggered() { emit paletteCmd(PaletteCommand::EDIT, id);    }
      void upTriggered()         { emit paletteCmd(PaletteCommand::UP, id);      }
      void downTriggered()       { emit paletteCmd(PaletteCommand::DOWN, id);    }
      void newTriggered()        { emit paletteCmd(PaletteCommand::NEW, id);     }

   public slots:
      void showPalette(bool);
      void enableEditing(bool);

   signals:
      void paletteCmd(PaletteCommand, int);
      void closeAll();

   public:
      PaletteBoxButton(Palette*, QWidget* parent = 0);
      void setId(int v) { id = v; }
      };


} // namespace Ms
#endif

