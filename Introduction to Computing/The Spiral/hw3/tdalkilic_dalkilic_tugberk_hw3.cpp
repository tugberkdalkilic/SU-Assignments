#include "robots.h"

bool controller (Robot& tgbrk)
{
	if (tgbrk.FacingWall())  // the case of checking robot goes to wall 
	{
		return false;
	}
	else
	{
		return true;
	}
}

void turnLeft(Robot& gomis)
{
	gomis.TurnRight();
	gomis.TurnRight();
	gomis.TurnRight();
}
bool movement1 (Robot& tgbrk, Robot& gomis)
{
	tgbrk.TurnRight();
	turnLeft(gomis);
	if (controller (tgbrk))
	{
		tgbrk.Move(1); // original robot goes 1 unit
		gomis.Move(1); // mirror robot goes 1 unit
		tgbrk.TurnRight();
		turnLeft(gomis);
		if (controller (tgbrk)) // system checks if original robot encounter a wall or not
		{
			tgbrk.Move(1);
			gomis.Move(1);

			tgbrk.TurnRight();
			turnLeft(gomis);
			if (controller (tgbrk))
			{
				tgbrk.Move(1);
				if (controller (tgbrk))
				{
					tgbrk.Move(1); 
					gomis.Move(2); // after 2 steps of original robot, mirror robot completes 2 steps

					tgbrk.TurnRight();
					turnLeft(gomis);
					if (controller (tgbrk))
					{
						tgbrk.Move();
						if (controller (tgbrk))
						{
							tgbrk.Move(); //last case of first spiral
							gomis.Move(2); 
							if (controller (tgbrk))
							{
								return true;
							}
							else 
								ShowMessage("Robots encountered a wall.End of the spiral."); // if the last case does not happen
						}
						else 
							ShowMessage("Robots encountered a wall.End of the spiral.");
					}
					else 
						ShowMessage("Robots encountered a wall.End of the spiral.");
				}
				else 
					ShowMessage("Robots encountered a wall.End of the spiral.");
			}
			else 
				ShowMessage("Robots encountered a wall.End of the spiral.");
		}
		else 
			ShowMessage("Robots encountered a wall.End of the spiral.");
	}
	else 
		ShowMessage("Robots encountered a wall.End of the spiral.");

	return false;
}

void movement2 (Robot& tgbrk, Robot& gomis)
{      
	tgbrk.TurnRight();
	turnLeft(gomis);
	if (controller (tgbrk))
	{
		tgbrk.Move();
		if (controller (tgbrk))
		{
			tgbrk.Move();
			if (controller (tgbrk))
			{
				tgbrk.Move();
				gomis.Move(3);

				tgbrk.TurnRight();
				turnLeft(gomis);
				if (controller (tgbrk))
				{
					tgbrk.Move();
					if (controller (tgbrk))
					{
						tgbrk.Move();
						if (controller (tgbrk))
						{
							tgbrk.Move();
							gomis.Move(3);

							tgbrk.TurnRight();
							turnLeft(gomis);
							if (controller (tgbrk))
							{
								tgbrk.Move();
								if (controller (tgbrk))
								{
									tgbrk.Move();
									if (controller (tgbrk))
									{ 
										tgbrk.Move();
										if (controller (tgbrk))
										{
											tgbrk.Move(); // original robot completes the 4th step
											gomis.Move(4); // after 4 steps of original robot, mirror robot completes 4 steps

											tgbrk.TurnRight();
											turnLeft(gomis);
											if (controller (tgbrk))
											{
												tgbrk.Move();
												if (controller (tgbrk))
												{
													tgbrk.Move();
													if (controller (tgbrk))
													{
														tgbrk.Move();
														if (controller (tgbrk))
														{
															tgbrk.Move();
															gomis.Move(4); // after completing of 4 steps for original robot, mirror robot moves 4 steps
															ShowMessage("Robots completed the spiral."); // if the all cases are true and robot does not encounter a wall
														}

													}
													else 
														ShowMessage("Robots encountered a wall.End of the spiral.");
												}
												else 
													ShowMessage("Robots encountered a wall.End of the spiral.");
											}
											else 
												ShowMessage("Robots encountered a wall.End of the spiral.");
										}
										else 
											ShowMessage("Robots encountered a wall.End of the spiral.");
									}
									else 
									{
										gomis.Move(2); // if the original robot encounters a wall in 3rd step, mirror robot goes 2 steps
										ShowMessage("Robots encountered a wall.End of the spiral.");
									}
								}
								else
								{
									gomis.Move(); // if the original robot encounters a wall in 2nd step, mirror robot goes 1 step
									ShowMessage("Robots encountered a wall.End of the spiral.");
								}
							}
							else 
								ShowMessage("Robots encountered a wall.End of the spiral.");
						}
						else 
						{
							gomis.Move(2); // if the original robot encounters a wall in 3rd step, mirror robot goes 2 steps
							ShowMessage("Robots encountered a wall.End of the spiral.");
						}
					}
					else
					{
						gomis.Move();
						ShowMessage("Robots encountered a wall.End of the spiral.");
					}
				}
				else 
					ShowMessage("Robots encountered a wall.End of the spiral.");
			}
			else 
			{
				gomis.Move(2);
				ShowMessage("Robots encountered a wall.End of the spiral.");
			}
		}
		else
		{
			gomis.Move();
			ShowMessage("Robots encountered a wall.End of the spiral.");
		}

	}

}

int main()
{

	ShowMessage("Welcome to robot world");
	int xaxis, yaxis;
	GetInput("Enter x coord of the robot", xaxis);
	if(xaxis >= 0 && xaxis <= 11)
	{
		GetInput("Enter y coord of the robot", yaxis );
		if(yaxis >= 0 && yaxis <= 11)
		{
			Robot tgbrk(xaxis ,yaxis,east); // original robot
			Robot gomis(23-xaxis, yaxis, west); // mirror robot

			tgbrk.SetColor(blue); // first color of original robot
			gomis.SetColor(red); // first color of mirror robot

			if(movement1 (tgbrk, gomis)==true)
			{
				tgbrk.SetColor(green); // after completing of first spiral original robot turns to green
				gomis.SetColor(purple); // after completing of first spiral mirror robot turns to purple

				movement2 (tgbrk, gomis);
			}
		}
		else
			ShowMessage("Invalid y value"); // when the number that in y entered is not between 0 and 11
	}
	else
		ShowMessage("Invalid x value"); // when the number that in x entered is not between 0 and 11

	return 0;
}









