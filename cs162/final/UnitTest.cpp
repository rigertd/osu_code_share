/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               UnitTest.hpp
 *
 * Overview:
 *     Implementation for UnitTest class.
 ************************************************************************/
#include "UnitTest.hpp"
#include "Command.hpp"
#include "Item.hpp"
#include "BasicRoom.hpp"
#include "Player.hpp"

void UnitTest::test_Room()
{
    Result r;
    
    /**************************************************************************
     * constructor
     *************************************************************************/
    std::cout << "Creating 2 new BasicRoom objects...";
    Room *pRoom1 = new BasicRoom();
    Room *pRoom2 = new BasicRoom();
    assert(pRoom1->id == 1);
    assert(pRoom2->id == 2);
    assert(pRoom1->description == "A new basic room with no interactivity.\n");
    assert(pRoom1->items.size() == 0);
    assert(pRoom1->north == NULL);
    assert(pRoom1->south == NULL);
    assert(pRoom1->east == NULL);
    assert(pRoom1->west == NULL);
    assert(pRoom1->nextId == 3);
    assert(pRoom2->nextId == 3);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * getRoomId function
     *************************************************************************/
    std::cout << "Testing getRoomId...";
    assert(pRoom1->getRoomId() == pRoom1->id);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * setDescription function
     *************************************************************************/
    std::cout << "Testing setDescription...";
    r = pRoom1->setDescription("test description\n");
    assert(pRoom1->description == "test description\n");
    assert(r.type == Result::SUCCESS);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * addItem function
     *************************************************************************/
    std::cout << "Testing addItem...";
    // happy path
    Item *pItem = new Item();
    pItem->setDesc("You see an item here.");
    r = pRoom1->addItem(pItem);
    assert(r.type == Result::SUCCESS);
    assert(pRoom1->items.size() == 1);
    
    // null pointer
    r = pRoom2->addItem(NULL);
    assert(r.type == Result::FAILURE);
    assert(pRoom2->items.size() == 0);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * findItem function
     *************************************************************************/
    std::cout << "Testing findItem...";
    // happy path
    Item *pItem2 = pRoom1->findItem(pItem->getId());
    assert(pItem2);
    // not found
    pItem2 = pRoom1->findItem(0);
    assert(!pItem2);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * useItem(Item *) function
     *************************************************************************/
    std::cout << "Testing useItem(Item *)...";
    r = pRoom1->useItem(pItem);
    assert(r.type == Result::FAILURE);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * useItem(unsigned) function
     *************************************************************************/
    std::cout << "Testing useItem(unsigned)...";
    // item exists
    r = pRoom1->useItem(pItem->getId());
    assert(r.type == Result::FAILURE);
    
    // item doesn't exist -- doesn't matter for this room type
    r = pRoom1->useItem(100);
    assert(r.type == Result::FAILURE);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * setExit function
     *************************************************************************/
    std::cout << "Testing setExit...";
    // happy path
    r = pRoom1->setExit(NORTH, pRoom2);
    assert(r.type == Result::SUCCESS);
    assert(pRoom1->north == pRoom2);
    assert(pRoom2->south == pRoom1);
    
    // exit already exists
    Room *pRoom3 = new BasicRoom();
    r = pRoom1->setExit(NORTH, pRoom3);
    assert(r.type == Result::FAILURE);
    assert(pRoom1->north == pRoom2);
    assert(pRoom3->south == NULL);
    
    // east
    r = pRoom1->setExit(EAST, pRoom2);
    assert(r.type == Result::SUCCESS);
    assert(pRoom1->east == pRoom2);
    assert(pRoom2->west == pRoom1);
    
    // south
    r = pRoom1->setExit(SOUTH, pRoom2);
    assert(r.type == Result::SUCCESS);
    assert(pRoom1->south == pRoom2);
    assert(pRoom2->north == pRoom1);
    
    // west
    r = pRoom1->setExit(WEST, pRoom2);
    assert(r.type == Result::SUCCESS);
    assert(pRoom1->west == pRoom2);
    assert(pRoom2->east == pRoom1);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * view function
     *************************************************************************/
    std::cout << "Testing view..." << std::endl;
    std::cout << "\nEdit mode enabled:\n";
    pRoom1->view(true);
    std::cout << "\nEdit mode disabled:\n";
    pRoom1->view(false);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * removeItem function
     *************************************************************************/
    std::cout << "Testing removeItem...";
    // item not found
    r = pRoom1->removeItem(0);
    assert(r.type == Result::FAILURE);
    assert(pRoom1->items.size() == 1);
    
    // happy path
    r = pRoom1->removeItem(pItem->getId());
    assert(r.type == Result::SUCCESS);
    assert(pRoom1->items.size() == 0);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * setRequired function
     *************************************************************************/
    std::cout << "Testing setRequired...";
    r = pRoom1->setRequired(pItem);
    assert(r.type == Result::FAILURE);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * setTarget function
     *************************************************************************/
    std::cout << "Testing setTarget...";
    r = pRoom1->setTarget(pRoom2);
    assert(r.type == Result::FAILURE);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * toggle function
     *************************************************************************/
    std::cout << "Testing toggle...";
    r = pRoom1->toggle();
    assert(r.type == Result::FAILURE);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * destructor
     *************************************************************************/
    std::cout << "Deleting 3 BasicRoom objects..." << std::endl;
    delete pRoom1;
    delete pRoom2;
    delete pRoom3;
    pRoom1 = pRoom2 = pRoom3 = NULL;
    std::cout << "Passed!" << std::endl;
    
    delete pItem;
    delete pItem2;
    pItem = pItem2 = NULL;
}

void UnitTest::test_Item()
{
    /**************************************************************************
     * constructors
     *************************************************************************/
    std::cout << "Testing constructors...";
    Item itm;
    assert(itm.id == 1);
    assert(itm.realName.empty());
    assert(itm.names.size() == 0);
    assert(itm.desc.empty());
    assert(itm.size == 0);
    assert(itm.weight == 0);
    Item itm2("name");
    assert(itm2.id == 2);
    assert(itm2.realName == "name");
    assert(itm2.names.size() == 1);
    assert(itm2.desc.empty());
    assert(itm2.size == 0);
    assert(itm2.weight == 0);
    Item itm3("name2", 1, 2);
    assert(itm3.id == 3);
    assert(itm3.realName == "name2");
    assert(itm3.names.size() == 1);
    assert(itm3.desc.empty());
    assert(itm3.size == 1);
    assert(itm3.weight == 2);
    assert(Item::nextId == 4);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * addName function
     *************************************************************************/
    std::cout << "Testing addName function...";
    itm.addName("main");
    assert(itm.realName == "main");
    assert(itm.names.size() == 1);
    itm.addName("alt");
    assert(itm.realName == "main");
    assert(itm.names.size() == 2);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * hasName function
     *************************************************************************/
    std::cout << "Testing hasName function...";
    assert(itm.hasName("main"));
    assert(itm.hasName("alt"));
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * getDesc function
     *************************************************************************/
    std::cout << "Testing getDesc function...";
    assert(itm.getDesc() == itm.desc);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * getId function
     *************************************************************************/
    std::cout << "Testing getId function...";
    assert(itm.getId() == itm.id);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * getName function
     *************************************************************************/
    std::cout << "Testing getName function...";
    assert(itm.getName() == itm.realName);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * getSize function
     *************************************************************************/
    std::cout << "Testing getSize function...";
    assert(itm.getSize() == itm.size);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * getWeight function
     *************************************************************************/
    std::cout << "Testing getWeight function...";
    assert(itm.getWeight() == itm.weight);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * setDesc function
     *************************************************************************/
    std::cout << "Testing setDesc function...";
    itm.setDesc("foo");
    assert(itm.desc == "foo");
    std::cout << "Passed!" << std::endl;
}

void UnitTest::test_Command()
{
    Result r;
    std::string input;

    // printCommands function
    std::cout << "Printing all commands...\n";
    Command::printCommands(true);
    std::cout << std::endl << "Printing non-edit commands...\n";
    Command::printCommands(false);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * constructor
     *************************************************************************/
    std::cout << "Testing constructors...";
    Command c;
    assert(c.type == Command::INVALID_COMMAND);
    assert(c.argument.empty());
    assert(c.desc.empty());
    assert(!c.edit);
    Command c2(Command::WORLD_EXIT);
    assert(c2.type == Command::WORLD_EXIT);
    assert(c2.argument.empty());
    assert(c2.desc.empty());
    assert(!c2.edit);
    Command c3(Command::WORLD_SAVE, "description", true);
    assert(c3.type == Command::WORLD_SAVE);
    assert(c3.argument.empty());
    assert(c3.desc == "description");
    assert(c3.edit);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * read function
     *************************************************************************/
    std::cout << "Testing read function...";
    // happy path
    input = "north";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_MOVE_NORTH);
    assert(c.argument.empty());
    input = "n";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_MOVE_NORTH);
    assert(c.argument.empty());
    input = "east";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_MOVE_EAST);
    assert(c.argument.empty());
    input = "e";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_MOVE_EAST);
    assert(c.argument.empty());
    input = "south";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_MOVE_SOUTH);
    assert(c.argument.empty());
    input = "s";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_MOVE_SOUTH);
    assert(c.argument.empty());
    input = "west";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_MOVE_WEST);
    assert(c.argument.empty());
    input = "w";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_MOVE_WEST);
    assert(c.argument.empty());
    input = "take foo";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ITEM_TAKE);
    assert(c.argument == "foo");
    input = "drop foo";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ITEM_DROP);
    assert(c.argument == "foo");
    input = "use foo";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ITEM_USE);
    assert(c.argument == "foo");
    input = "inventory";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::PLAYER_INVENTORY);
    assert(c.argument.empty());
    input = "inv";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::PLAYER_INVENTORY);
    assert(c.argument.empty());
    input = "maxquantity 100";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::PLAYER_MAX_QUANTITY);
    assert(c.argument == "100");
    input = "maxsize 10";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::PLAYER_MAX_SIZE);
    assert(c.argument == "10");
    input = "maxweight 50";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::PLAYER_MAX_WEIGHT);
    assert(c.argument == "50");
    input = "dn";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_DELETE_NORTH);
    assert(c.argument.empty());
    input = "de";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_DELETE_EAST);
    assert(c.argument.empty());
    input = "ds";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_DELETE_SOUTH);
    assert(c.argument.empty());
    input = "dw";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::ROOM_DELETE_WEST);
    assert(c.argument.empty());
    input = "delroom";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_DELETE_ROOM);
    assert(c.argument.empty());
    input = "edit";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_EDIT);
    assert(c.argument.empty());
    input = "listitems";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_ITEM_LIST);
    assert(c.argument.empty());
    input = "listrooms";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_ROOM_LIST);
    assert(c.argument.empty());
    input = "save";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_SAVE);
    assert(c.argument.empty());
    input = "setend";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_SET_END);
    assert(c.argument.empty());
    input = "setstart";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_SET_START);
    assert(c.argument.empty());
    input = "timelimit 10";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_SET_TIME);
    assert(c.argument == "10");
    input = "exit";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_EXIT);
    assert(c.argument.empty());
    input = "quit";
    r = c.read(input, true);
    assert(r.type == Result::SUCCESS);
    assert(c.type == Command::WORLD_EXIT);
    assert(c.argument.empty());
    
    // invalid command
    input = "foo";
    r = c.read(input, true);
    assert(r.type == Result::FAILURE);
    assert(c.type == Command::INVALID_COMMAND);
    
    // empty command
    input = "";
    r = c.read(input, true);
    assert(r.type == Result::FAILURE);
    assert(c.type == Command::INVALID_COMMAND);
    
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * setArgument function
     *************************************************************************/
    std::cout << "Testing setArgument function...";
    c.setArgument("bar");
    assert(c.argument == "bar");
    c.setArgument("");
    assert(c.argument.empty());
    
    std::cout << "Passed!" << std::endl;
}

void UnitTest::test_Player()
{
    Result r;

    /**************************************************************************
     * constructor
     *************************************************************************/
    std::cout << "Testing constructor...";
    Room *rm = new BasicRoom();
    Player p(NULL, rm);
    assert(p.location == rm);
    assert(p.inventory.size() == 0);
    assert(p.weightLimit = 100);
    assert(p.maxSize == 10);
    assert(p.maxQuantity == 5);
    Player p2(NULL, rm, 1, 2, 3);
    assert(p2.location == rm);
    assert(p2.inventory.size() == 0);
    assert(p2.weightLimit = 1);
    assert(p2.maxSize == 2);
    assert(p2.maxQuantity == 3);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * take function
     *************************************************************************/
    std::cout << "Testing take...";
    Item *itm1 = new Item("key1");
    Item *itm2 = new Item("key2",2,1);
    Item *itm3 = new Item("key3",2,0);
    Item *itm4 = new Item("key4",2,0);
    Item *itm5 = new Item("key5",3,0);
    Item *itm6 = new Item("key6",2,1);
    rm->addItem(itm1);
    rm->addItem(itm2);
    rm->addItem(itm3);
    rm->addItem(itm4);
    rm->addItem(itm5);
    rm->addItem(itm6);
    // item not found
    r = p2.take(100);
    assert(r.type == Result::FAILURE);
    assert(p2.inventory.size() == 0);
    assert(rm->items.size() == 6);
    // happy path
    r = p2.take(itm1->getId());
    assert(r.type == Result::SUCCESS);
    assert(p2.inventory.size() == 1);
    assert(rm->items.size() == 5);
    // boundary (weight and size limit)
    r = p2.take(itm2->getId());
    assert(r.type == Result::SUCCESS);
    assert(p2.inventory.size() == 2);
    assert(rm->items.size() == 4);
    // boundary (size too big by 1)
    r = p2.take(itm5->getId());
    assert(r.type == Result::FAILURE);
    assert(p2.inventory.size() == 2);
    assert(rm->items.size() == 4);
    // boundary (total weight over)
    r = p2.take(itm6->getId());
    assert(r.type == Result::FAILURE);
    assert(p2.inventory.size() == 2);
    assert(rm->items.size() == 4);
    // boundary (exact quantity limit)
    r = p2.take(itm3->getId());
    assert(r.type == Result::SUCCESS);
    assert(p2.inventory.size() == 3);
    assert(rm->items.size() == 3);
    // boundary (quantity over by 1)
    r = p2.take(itm4->getId());
    assert(r.type == Result::FAILURE);
    assert(p2.inventory.size() == 3);
    assert(rm->items.size() == 3);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * getInventoryWeight function
     *************************************************************************/
    std::cout << "Testing getInventoryWeight...";
    assert(p2.getInventoryWeight() == 1);
    assert(p.getInventoryWeight() == 0);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * dropItem function
     *************************************************************************/
    std::cout << "Testing dropItem...";
    // item not found
    r = p2.dropItem(100);
    assert(r.type == Result::FAILURE);
    assert(p2.inventory.size() == 3);
    assert(rm->items.size() == 3);
    // happy path
    r = p2.dropItem(itm1->getId());
    assert(r.type == Result::SUCCESS);
    assert(p2.inventory.size() == 2);
    assert(rm->items.size() == 4);
    std::cout << "Passed!" << std::endl;
    
    /**************************************************************************
     * getCurrentRoom function
     *************************************************************************/
    std::cout << "Testing getCurrentRoom...";
    assert(p2.getCurrentRoom() == p2.location);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * move function
     *************************************************************************/
    std::cout << "Testing move...";
    Room *rm2 = new BasicRoom();
    rm->setExit(NORTH, rm2);
    r = p2.move(NORTH);
    assert(r.type == Result::SUCCESS);
    assert(p2.location == rm2);
    r = p2.move(SOUTH);
    assert(r.type == Result::SUCCESS);
    assert(p2.location == rm);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * useItem function
     *************************************************************************/
    std::cout << "Testing useItem...";
    // item in inventory
    r = p2.useItem(itm2->getId());
    assert(r.type == Result::FAILURE);
    // item in room
    r = p2.useItem(itm6->getId());
    assert(r.type == Result::FAILURE);
    std::cout << "Passed!" << std::endl;

    /**************************************************************************
     * viewItems function
     *************************************************************************/
    std::cout << "Testing viewItems..." << std::endl;
    p2.viewItems();
    std::cout << "Passed!" << std::endl;

    // free memory allocated from heap
    delete itm1;
    delete itm2;
    delete itm3;
    delete itm4;
    delete itm5;
    delete itm6;
    delete rm;
    delete rm2;
    itm1 = itm2 = itm3 = itm4 = itm5 = itm6 = NULL;
    rm = rm2 = NULL;
}