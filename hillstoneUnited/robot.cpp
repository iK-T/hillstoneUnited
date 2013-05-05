#include "robot.hpp"

Robot::Robot(std::string teamname){
  world.setTeamname(teamname);
  virgin = true;
}

Robot::~Robot(){}

std::string Robot::getNextAngle(std::string &msg){
  
  world.update(msg);
  world.dump();


  /**
  brain.checkResponse(world);
  brain.updateList();
  if(brain.allListEmpty()){
      brain.think(world);
  }
  return brain.getString(world);
  **/
  //return "hogehoge in robot"; // I'll change it

  //  static double initpos[3] = {-10.5, 0.0, 0.0};
  static double initpos1[3] = {-14.5,0.0, 0.0};
  static double initpos2[3] = {-11.5,3.0, 0.0};
  static double initpos3[3] = {-11.5,-3.0, 0.0};
  static double initpos4[3] = {-11.5,0.0, 0.0};
  static double initpos5[3] = {-8.5,1.0, 0.0};
  static double initpos6[3] = {-8.5,-1.0, 0.0};
  static double initpos7[3] = {-5.5,2.0, 0.0};
  static double initpos8[3] = {-5.5,-2.0, 0.0};
  static double initpos9[3] = {-2.5,3.0, 0.0};
  static double initpos10[3] = {-0.5,0.0, 0.0};
  static double initpos11[3] = {-2.5,-3.0, 0.0};

  /*

  mainbrain = new TestBrain(world, initpos9);
  if (mainbrain->isFinished())
  {
    delete mainbrain;
    mainbrain = new TestBrain(world, initpos9);
  }
  return mainbrain->getNextAngle(world);

  */

  
  if (world.getUnum() > 0){
    if (virgin){


      // int unum = world.getUnum();
      // double tmp[3] {tmpinit[unum][0], tmpinit[unum][1], tmpinit[unum][2]};
      // mainbrain = new Attack(world, tmp);

      switch(world.getUnum()){
      case 1:
	//	mainbrain = new Keeper(world, initpos1);
	mainbrain = new Defend(world, initpos2);
	break;
      case 2:
	mainbrain = new Defend(world, initpos3);
	break;
      case 3:
	mainbrain = new Defend(world, initpos4);
	break;


      case 4:
	mainbrain = new Defend(world, initpos4);
	break;
      case 5:
	mainbrain = new Defend(world, initpos5);
	break;
      case 6:
	mainbrain = new Defend(world, initpos6);
	break;
      case 7:
	mainbrain = new Attack(world, initpos7);
	break;
      case 8:
	mainbrain = new Attack(world, initpos8);
	break;
      case 9:
	mainbrain = new Attack(world, initpos9);
	break;
      case 10:
	mainbrain = new Attack(world, initpos10);
	break;
      case 11:
	mainbrain = new Attack(world, initpos11);
	break;
      }
      virgin = false;
      
    }else{
      
      if (mainbrain->isFinished()){
	delete mainbrain;
	// mainbrain = new Attack(world, initpos);
	//      mainbrain = new Defend(world, initpos);
	switch(world.getUnum()){
	case 1:
	  //	  mainbrain = new Keeper(world, initpos1);
	  mainbrain = new Defend(world, initpos2);
	  break;
	case 2:
	  mainbrain = new Defend(world, initpos3);
	  break;
	case 3:
	  mainbrain = new Defend(world, initpos4);
	  break;


	case 4:
	  mainbrain = new Defend(world, initpos4);
	  break;
	case 5:
	  mainbrain = new Defend(world, initpos5);
	  break;
	case 6:
	  mainbrain = new Defend(world, initpos6);
	  break;
	case 7:
	  mainbrain = new Attack(world, initpos7);
	  break;
	case 8:
	  mainbrain = new Attack(world, initpos8);
	  break;
	case 9:
	  mainbrain = new Attack(world, initpos9);
	  break;
	case 10:
	  mainbrain = new Attack(world, initpos10);
	  break;
	case 11:
	  mainbrain = new Attack(world, initpos11);
	  break;
	default:
	  mainbrain = new Attack(world, initpos3);
	  break;
	}
	
        std::cout << "finish!!" << std::endl;
      }
      
    }
    return mainbrain->getNextAngle(world);
  } 
  return "";
  
}
  
std::string Robot::Init2(){
  return "(init (unum 0)(teamname " + world.getTeamname() + "))";
}
