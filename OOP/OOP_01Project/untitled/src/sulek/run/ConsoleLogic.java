package sulek.run;

import sulek.entity.Enemy;
import sulek.entity.Player;

public class ConsoleLogic {
    public void blankSpaces(){
        for (int i = 0; i < 10; i++){
            System.out.println("\n");
        }
    }
    public void line(){
        System.out.println("------------------");
    }

    public void report(Player player, Enemy enemy){
        System.out.println(" -------------------");
        System.out.println("| " + player.getName() +" Health  "+ player.getHp());
        System.out.println("| " + enemy.getName() + " Health  "+ enemy.getHp());
        System.out.println(" -------------------");
    }
}
