TEMPLATE = app
TARGET   = QtCraft
QT      += core gui multimedia opengl
INCLUDEPATH += .

HEADERS += inputhandler.h \
           game.h \
           entity/entity.h \
           entity/mob.h \
           entity/player.h \
           gfx/screen.h \
           gfx/spritesheet.h \
           level/level.h \
           screen/menu.h \
           screen/titlemenu.h \
           gfx/color.h \
           gfx/font.h \
           screen/instructionsmenu.h \
           screen/aboutmenu.h \
           item/item.h \
           item/ilistitem.h \
    entity/inventory.h \
    level/tile/tile.h \
    level/tile/grasstile.h \
    item/toolitem.h \
    item/tooltype.h \
    entity/particle/textparticle.h \
    gaussianrand.h \
    level/levelgen.h \
    level/tile/rocktile.h \
    entity/particle/smashparticle.h \
    level/tile/watertile.h \
    level/tile/flowertile.h \
    level/tile/treetile.h \
    item/resource.h \
    item/foodresource.h \
    item/plantableresource.h \
    sound.h \
    screen/inventorymenu.h \
    entity/zombie.h \
    item/resourceitem.h \
    entity/itementity.h \
    entity/furniture.h \
    item/powergloveitem.h \
    item/furnitureitem.h \
    screen/deadmenu.h \
    level/tile/sandtile.h \
    level/tile/stairstile.h \
    level/tile/cactustile.h \
    level/tile/hardrocktile.h \
    entity/furnace.h \
    entity/workbench.h \
    crafting/crafting.h \
    crafting/recipe.h \
    crafting/toolrecipe.h \
    screen/craftingmenu.h \
    crafting/furniturerecipe.h \
    level/tile/dirttile.h \
    level/tile/holetile.h \
    level/tile/farmtile.h \
    level/tile/saplingtile.h \
    crafting/resourcerecipe.h \
    level/tile/wheattile.h \
    entity/anvil.h \
    entity/chest.h \
    entity/lantern.h \
    entity/oven.h \
    level/tile/infinitefalltile.h \
    screen/containermenu.h \
    leveled.h \
    level/tile/lavatile.h \
    level/tile/cloudtile.h \
    level/tile/oretile.h \
    screen/leveltransitionmenu.h \
    entity/slime.h \
    level/tile/cloudcactustile.h \
    screen/wonmenu.h \
    entity/airwizard.h \
    entity/spark.h

SOURCES += inputhandler.cpp \
           game.cpp \
           main.cpp \
           entity/entity.cpp \
           entity/mob.cpp \
           entity/player.cpp \
           gfx/screen.cpp \
           gfx/spritesheet.cpp \
           level/level.cpp \
           screen/menu.cpp \
           screen/titlemenu.cpp \
           gfx/color.cpp \
           gfx/font.cpp \
           screen/instructionsmenu.cpp \
           screen/aboutmenu.cpp \
           item/item.cpp \
    entity/inventory.cpp \
    level/tile/tile.cpp \
    level/tile/grasstile.cpp \
    item/toolitem.cpp \
    item/tooltype.cpp \
    entity/particle/textparticle.cpp \
    gaussianrand.cpp \
    level/levelgen.cpp \
    level/tile/rocktile.cpp \
    entity/particle/smashparticle.cpp \
    level/tile/watertile.cpp \
    level/tile/flowertile.cpp \
    level/tile/treetile.cpp \
    item/resource.cpp \
    item/foodresource.cpp \
    item/plantableresource.cpp \
    sound.cpp \
    screen/inventorymenu.cpp \
    entity/zombie.cpp \
    item/resourceitem.cpp \
    entity/itementity.cpp \
    entity/furniture.cpp \
    item/powergloveitem.cpp \
    item/furnitureitem.cpp \
    screen/deadmenu.cpp \
    level/tile/sandtile.cpp \
    level/tile/stairstile.cpp \
    level/tile/cactustile.cpp \
    level/tile/hardrocktile.cpp \
    entity/furnace.cpp \
    entity/workbench.cpp \
    crafting/crafting.cpp \
    crafting/recipe.cpp \
    crafting/toolrecipe.cpp \
    screen/craftingmenu.cpp \
    level/tile/dirttile.cpp \
    level/tile/holetile.cpp \
    level/tile/farmtile.cpp \
    level/tile/saplingtile.cpp \
    crafting/resourcerecipe.cpp \
    level/tile/wheattile.cpp \
    entity/anvil.cpp \
    entity/chest.cpp \
    entity/lantern.cpp \
    entity/oven.cpp \
    level/tile/infinitefalltile.cpp \
    screen/containermenu.cpp \
    leveled.cpp \
    level/tile/lavatile.cpp \
    level/tile/cloudtile.cpp \
    level/tile/oretile.cpp \
    screen/leveltransitionmenu.cpp \
    entity/slime.cpp \
    level/tile/cloudcactustile.cpp \
    screen/wonmenu.cpp \
    entity/airwizard.cpp \
    entity/spark.cpp

RESOURCES += \
    res/res.qrc
