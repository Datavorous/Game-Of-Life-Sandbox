
class bonus_java_terminal
{
	public static int grid[][] = {};
      
        //Insert grid here from grid.txt
	public static int grid2[][] = new int[grid.length][grid[0].length];

	public static int generations = 100;
	public static float fps = 4;				 

	public static void main(String[] args)throws InterruptedException
	{	

		for (int i=0;i<grid2.length ;i++ )
			for(int j=0;j<grid2[0].length;j++)
				grid2[i][j] = 0;

		for(int gen=1;gen<=generations;gen++)
		{
			drawGrid();
			Thread.sleep((int)((1/fps)*1000));
			implementRules();
			updateGrids();

			
		}
		System.gc();
	}

	static void drawGrid()
	{
		for(int row=0;row<grid.length;row++)
			{
				for (int column=0;column<grid[0].length;column++)
				{
					if(grid[row][column]==0)
						System.out.print(". ");
					else
						System.out.print("■ ");
				}
				System.out.println();
			}
		System.out.println();
	}

	static void implementRules()
	{
		for(int row=1;row<=grid.length-2;row++)
			{
				for(int column=1;column<=grid[0].length-2;column++)
				{
					int alive = 0;

					for(int i=-1;i<=1;i++)
						for(int j = -1 ; j <= 1; j++)
							alive += grid[row+i][column+j];
					alive -= grid[row]	[column];

					if((grid[row][column]==1) && (alive<2))
						grid2[row][column] = 0;
					else if((grid[row][column]==1) && (alive>3))
						grid2[row][column] = 0;
					else if((grid[row][column]==0) && (alive==3))
						grid2[row][column] = 1;
					else
						grid2[row][column] = grid[row][column];
				}
			}
	}
	
	static void updateGrids()
	{
		for (int i = 0;i<grid.length ;i++ )
			for (int j=0;j<grid[0].length ;j++ )
				grid[i][j] = grid2[i][j];

		for (int i = 0;i<grid.length ;i++ )
			for (int j=0;j<grid[0].length ;j++ )
				grid2[i][j] = 0;
	}

	
}
