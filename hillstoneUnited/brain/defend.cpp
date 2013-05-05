#include "defend.hpp"

// choose the one, and off the rest.
#define LAB
//#define TEST1 // Defend: Default ver.
//#define TEST2 // prototype
//#define TEST3 // prototype2

Defend::Defend(World& w, double _initpos[]){
  finish_flag = false;
  beam_flag = false;
  start_flag = false;

  xy[0] = w.getXY(0);
  xy[1] = w.getXY(1);
  bxy[0] = w.getBXY(0);
  bxy[1] = w.getBXY(1);
  bal[0] = w.getBAL(0);
  bal[1] = w.getBAL(1);
  bal[2] = w.getBAL(2);
  bxy_conf = w.confBAL();
  xy_conf = w.confXY();
  bal_conf = w.confBAL();
  angle = w.getABSANGLE();
  dist = 0.0;

  for(int i=0; i<11; i++){
    for(int j=0; j<4; j++){
      friends[i][j] = w.getFRIEND(i, j);
      enemy[i][j] = w.getENEMY(i, j);
    }
  }

  field_x = w.getFieldLengthX();
  field_y = w.getFieldLengthY();

  initpos[0] = _initpos[0];
  initpos[1] = _initpos[1];
  initpos[2] = _initpos[2];
  //  elementList.push_back(new SequenceMovement("LAROUND"));
  judgement(w);
}

void Defend::judgement(World& w){

  bxy[0] = w.getBXY_AVE(0);
  bxy[1] = w.getBXY_AVE(1);
  bal[0] = w.getBAL(0);
  bal[1] = w.getBAL(1);
  bal[2] = w.getBAL(2);
  xy[0] = w.getXY_AVE(0);
  xy[1] = w.getXY_AVE(1);
  bxy_conf = w.confBAL();
  xy_conf = w.confXY();
  angle = w.getABSANGLE();
  dist = sqrt(((initpos[0] - xy[0])*(initpos[0] - xy[0]))
	      + ((initpos[1] - xy[1])*(initpos[1] - xy[1])));

  t_count = abs(15 * bal[1] / 360);
  if(t_count == 0){
    t_count = 1;
  }
  
  for(int i=0; i<11; i++){
    for(int j=0; j<4; j++){
      friends[i][j] = w.getFRIEND(i, j);
      enemy[i][j] = w.getENEMY(i, j);
    }
  }

  judgeStandup(w);

#ifdef LAB

  if(bxy_conf != 300 && bal[0] < 1.5){
    std::cout << "near ball " << bal[0] << std::endl;
    elementList.push_back(new OdensWalk(bxy));
  }
  else{
    std::cout << "not near ball " << bal[0] << std::endl;
    //    elementList.push_back(new SequenceMovement("DUMMY"));
    elementList.push_back(new SequenceMovement("LAROUNDREADY"));
  }


#endif
#ifdef TEST1


  if(inTerritory()){
    //    std::cout << "in my Territory." << std::endl;
    if(bxy_conf==300 && xy_conf==300){
      elementList.push_back(new TicktackBase("TLEFT", 2));
    }
    else if(bxy_conf==300){
      elementList.push_back(new TicktackBase("TLEFT", t_count));
      elementList.push_back(new SequenceMovement("LAROUND"));
    }
    else{
      if(close2Bal() && towardEnemy()){
	//          std::cout << "close to ball" << std::endl;
	if(bal[0] > 10){
	  elementList.push_back(new TicktackBase("TLEFT", t_count));
	}
	else if(bal[0] < -10){
	  elementList.push_back(new TicktackBase("TRIGHT", t_count));
	}
	else{
	  elementList.push_back(new SequenceMovement("DUMMY"));
	  elementList.push_back(new TicktackBase("FORWARD", 2));
	  elementList.push_back(new GABase("GA_FORWARD", 5));
	}
	//	  elementList.push_back(new KickTo(w, 0));
      }else{
	if(getInvader()>0){
	  //            std::cout << "invader, invader!" << std::endl;
	  elementList.push_back(new RunToEnemy(w, getInvader()));
	}
	else{
	  if(bal[0] < 2.0){
	    //              std::cout << "chuuto hanpa" << std::endl;
	    // elementList.push_back(new RunTo(w, ballpos));
	    elementList.push_back(new OdensWalk(bxy));
	  }else{
	    //              std::cout << "not close to ball" << std::endl;
	    elementList.push_back(new RunToBall(w));
	  }
	}
      }
    }
  }else{
    //    std::cout << "not in my Territory." << std::endl;
    if(bxy_conf==300 && xy_conf==300){
      elementList.push_back(new SequenceMovement("DUMMY"));
      elementList.push_back(new SequenceMovement("LAROUND"));
      elementList.push_back(new TicktackBase("TLEFT", 2));
    }
    else{
      if(atHome()){
        if(bxy_conf==300 && xy_conf==300){
          elementList.push_back(new TicktackBase("TLEFT", 2));
        }
        else if(xy_conf==300){
          elementList.push_back(new SequenceMovement("DUMMY"));
          elementList.push_back(new SequenceMovement("LAROUND"));
        }
        else{
          if(bal[1] > 0){
            elementList.push_back(new TicktackBase("TLEFT", t_count));
          }
          else{
            elementList.push_back(new TicktackBase("TRIGHT", t_count));
          }
        }
      }
      else{
        double home[2];
        for(int i=0; i<2; i++){
          home[i] = initpos[i];
        }
        elementList.push_back(new OdensWalk(home));
      }
    }
  }
  // elementList.push_back(new SequenceMovement("DUMMY"));
  // elementList.push_back(new SequenceMovement("LAROUND"));


#endif
#ifdef TEST2

  if(bxy_conf == 300){
    elementList.push_back(new SequenceMovement("LAROUNDREADY"));
  }
  else{
    if(inDanger()){
      if(inTerritory()){
	int invader = getInvader();
	if(invader > 0){
	  elementList.push_back(new RunToEnemy(w, invader));
	  elementList.push_back(new OdensWalk(bxy));
	}
	else{
	  elementList.push_back(new RunToBall(w));
	  elementList.push_back(new AdjustToBall(w));
	  if(abs(bxy[0]-(-15.0)) > 5.0 && abs(bxy[1]-0.0) > 5.0){
	    elementList.push_back(new SequenceMovement("READY"));
	    elementList.push_back(new GABase("GA_FORWARD", 10));
	  }
	  else{
	    if(bal[1]>0){
	      elementList.push_back(new KickTo(w, 90));
	    }
	    else{
	      elementList.push_back(new KickTo(w, -90));
	    }
	  }
	}
      }
      else{
	elementList.push_back(new SequenceMovement("LAROUNDREADY"));
      }
    }
    else{
      if(!atHome()){
	double home[2];
	home[0] = initpos[0];
	home[1] = initpos[1];
	elementList.push_back(new SequenceMovement("READY"));
	elementList.push_back(new RunTo(w, home));
      }
      else{
	if(bal[1]>10){
	  elementList.push_back(new SequenceMovement("READY"));
	  elementList.push_back(new TicktackBase("TLEFT", t_count));
	}
	else if(bal[1]<-10){
	  elementList.push_back(new SequenceMovement("READY"));
	  elementList.push_back(new TicktackBase("TRIGHT", t_count));
	}
	else{
	  elementList.push_back(new SequenceMovement("LAROUNDREADY"));
	}
      }
    }
  }

#endif
#ifdef TEST3

  if(bxy_conf == 300){
    elementList.push_back(new SequenceMovement("LAROUNDREADY"));
  }
  else{
    if(inDanger()){
      if(inTerritory()){
	int invader = getInvader();
	if(invader > 0){
	  elementList.push_back(new RunToEnemy(w, invader));
	  elementList.push_back(new OdensWalk(bxy));
	}
	else{
	  elementList.push_back(new OdensWalk(bxy));
	}
      }
    }
    else{
      if(!atHome()){
	double home[2];
	home[0] = initpos[0];
	home[1] = initpos[1];
	elementList.push_back(new OdensWalk(home));
      }
      else{
	elementList.push_back(new SequenceMovement("LAROUNDREADY"));
      }
    }
  }



#endif

}

bool Defend::inTerritory(){
  if(abs(bxy[0] - initpos[0]) < 8.0 &&
     abs(bxy[1] - initpos[1]) < 8.0){
    return true;
  }else{
    return false;
  }
}

bool Defend::atHome(){
  if(abs(xy[0] - initpos[0]) < 0.5 &&
     abs(xy[1] - initpos[1]) < 0.5){
    return true;
  }else{
    return false;
  }
}

bool Defend::close2Bal(){
  if(abs(bal[0]) < 0.9){
    return true;
  }else{
    return false;
  }
}

bool Defend::towardEnemy(){
  if(abs(angle) < 60){
    return true;
  }else{
    return false;
  }
}

bool Defend::inDanger(){
  if(bxy[0] < -(field_x/6)){
    return true; 
 }else{
    return false;
  }
}

void Defend::updateFinishFlag(World& w){
  judgement(w);
}

int Defend::getInvader(){
  int nearest = 0;
  double dist = 1000;
  for(int i=0; i<10; i++){
    if(abs(enemy[i][0] - bal[0]) < 3.0 &&
       abs(enemy[i][1] - bal[1]) < 30 &&
       enemy[i][3] != 0){
      if(abs(enemy[i][0] - bal[0]) < dist){
	dist = abs(enemy[i][0] - bal[0]);
	nearest = i;
      }
    }
  }
  if(nearest!=0){
    return nearest;
  }
  else{
    return 0;
  }
}


std::string Defend::getNextAngle(World& w) {
  std::stringstream ss;
  if((w.getPlaymode()=="BeforeKickOff" ||
      w.getPlaymode()=="Goal_Left" ||
      w.getPlaymode()=="Goal_Right") && w.getUnum()>0){
    beam_flag = true;
    ss << "(beam " << initpos[0] << " "
       << initpos[1] << " " << initpos[2]
       << ")";
    // std::cout << ss.str() << std::endl;
    while(!elementList.empty()){
      ElementBase* tmp = elementList.front();
      delete tmp;
      elementList.pop_front();
    }
    elementList.push_back(new SequenceMovement("DUMMY"));
  }
  
  if((w.getPlaymode()=="KickOff_left" || w.getPlaymode()=="KickOff_Right") && start_flag == true){
    elementList.push_back(new SequenceMovement("DUMMY"));
    start_flag = false;
  }
  
  if (w.isFalling())
    {
      if (pushStand)
        {
	  /* code */
        } else {
	for(std::deque<ElementBase*>::iterator it=elementList.begin();
	    it != elementList.end(); ++it){
	  delete (*it);
	}
	elementList.clear();
	elementList.push_front(new Standup());
	pushStand = true;
      }
    } else {
    pushStand = false;
  }

  rtn = elementList.front()->getNextAngle(w);
  if(beam_flag){
    rtn += ss.str();
    beam_flag = false;
  }
  if (elementList.front()->isFinished())
    {
      ElementBase* tmp = elementList.front();
      delete tmp;
      elementList.pop_front();
    }
  if (finishAllChild(w))
    {
      updateFinishFlag(w);
    }
  return rtn;
}

