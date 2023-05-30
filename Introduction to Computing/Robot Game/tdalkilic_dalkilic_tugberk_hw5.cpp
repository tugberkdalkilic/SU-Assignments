#include "Robots_Modified.h"
#include "randgen.h"
#include "MiniFW_Modified.h"

void randomMove(Robot & monst1, Robot& monst2 , Robot & monst3 , Robot& monst4) //randomly choosing which monster will move
{
	RandGen gen;
	int rnd = gen.RandInt(1,4);
	if (rnd == 1)
	{	
		if (monst1.FacingWall())
			monst1.TurnBack();
		monst1.Move();
	}   
	else if (rnd ==2)
	{
		if(monst2.FacingWall())
			monst2.TurnRight();
		else
			monst2.Move();
	}
	else if (rnd ==3)
	{
		if(monst3.FacingWall())
			monst3.TurnRight();
		else
			monst3.Move();
	}
	else if (rnd ==4)
	{	
		if (monst4.FacingWall())
			monst4.TurnBack();
		monst4.Move();
	}
}
void Res_all(Robot & monst1, Robot& monst2 , Robot & monst3 , Robot& monst4) //if monster dies it resurrects itself
{
	if(!monst1.IsAlive())
		monst1.Resurrect();
	if(!monst2.IsAlive())
		monst2.Resurrect();
	if(!monst3.IsAlive())
		monst3.Resurrect();
	if(!monst4.IsAlive())
		monst4.Resurrect();
}

int main()
{
	Robot tugberk (0,4,east);
	Robot monst1(3,8,south);
	Robot monst2(6,2,east);
	Robot monst3(13,5,east);
	Robot monst4(13,0,north);
	monst1.SetColor(red);
	monst2.SetColor(blue);
	monst3.SetColor(blue);
	monst4.SetColor(red);

	int count =3;
	bool flag=true; // terminating the game after the game finishes
	bool spacenotmove=true; // pressing space key
	while(count > 0 && flag==true)
	{
		Res_all(monst1,monst2,monst3,monst4);
		if (spacenotmove)

			randomMove(monst1,monst2,monst3,monst4);

		if (IsPressed(keyRightArrow))
		{
			tugberk.TurnFace(east);
			tugberk.PickAllThings();

		}
		else if (IsPressed(keyUpArrow))
		{
			tugberk.TurnFace(north);
			tugberk.PickAllThings();

		}
		else if (IsPressed(keyDownArrow))
		{
			tugberk.TurnFace(south);
			tugberk.PickAllThings();

		}
		else if (IsPressed(keySpace) && tugberk.GetBagCount() >=20)
		{
			tugberk.SetBagCount(tugberk.GetBagCount()-20);
			spacenotmove =false;
			if ((monst1.GetXCoordinate() == 14 && monst1.GetYCoordinate() == 4) || (monst2.GetXCoordinate() == 14 && monst2.GetYCoordinate() == 4) || (monst3.GetXCoordinate() == 14 && monst3.GetYCoordinate() == 4) || (monst4.GetXCoordinate() == 14 && monst4.GetYCoordinate() == 4 ))
				ShowMessage("You blocked the target… You lost the Game!");
		}
		if (!tugberk.IsAlive())
		{
			if (count ==3)
			{
				ShowMessage("You have 2 lives left.");
				tugberk.Resurrect();
				//randomMove( monst1, monst2 , monst3 , monst4);
				//monst1.Resurrect(); monst2.Resurrect();monst3.Resurrect();monst4.Resurrect();
				count--;
			}
			else if (count ==2)
			{
				ShowMessage("You have 1 live left."); 
				tugberk.Resurrect();
				//randomMove(monst1, monst2 , monst3 , monst4);
				//monst1.Resurrect(); monst2.Resurrect();monst3.Resurrect();monst4.Resurrect();
				count--;
			}
			else if (count ==1)
			{
				ShowMessage("You run out of lives… You lost the Game!");
				//monst1.Resurrect(); monst2.Resurrect();monst3.Resurrect();monst4.Resurrect();
				count--;
			}

		}
		if (tugberk.IsAlive() && tugberk.GetBagCount()>=50 && tugberk.GetXCoordinate()==14 && tugberk.GetYCoordinate() ==4) // case of finishing the game with more than 50points
		{
			ShowMessage("Congratulations, you win!");
			flag =false;
		}
		else if (tugberk.IsAlive() && tugberk.PickThing()<50 && tugberk.GetXCoordinate()==14 && tugberk.GetYCoordinate() ==4 ) // case of not getting more than 50 things but reaching target point
		{
			ShowMessage("You reached the end but could not gather enough things… You lost the Game!");
			flag=false;
		}
	}
}
/*1. GetXCoordinate: A member function that returns the X coordinate of the robot object.
2. GetYCoordinate: A member function that returns the Y coordinate of the robot object.
3. TurnBack: A member function that turns the robot object to the opposite direction it is facing.
4. TurnFace: A member function that takes a Direction type (this is an enumerated type defined
in robot header file) parameter and turns the robot object towards this direction.
5. GetBagCount: A member function that returns the number of things in the robot’s bag.
6. SetBagCount: A member function that sets the number of things in the robot’s bag. This
function will be useful to deduce 20 things from the player robot’s bag when STOP action is
invoked.
7. IsAlive: A member function to check if the robot object is alive.
8. Resurrect: A member function to resurrect the robot object. Hint: play with stalled private
data member for the implementation.
9. PickAllThings: A member function that allows the robot object to pick all the things in the
occupied cell.
*/