package sulek.run;

import sulek.entity.*;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Game {
    Player player;
    Enemy enemy;
    Enemy snake;
    Enemy ghost;
    Enemy skeleton;
    Scanner scanner = new Scanner(System.in);
    ConsoleLogic consoleLogic = new ConsoleLogic();
    ArrayList<Enemy> enemyArrayList = new ArrayList<>();
    public void battle(Player player, Enemy enemy){
        System.out.println("1: Attack       2: Escape\n");
        if (player.getSpeed() >= enemy.getSpeed()){
            player.attack(enemy);
            enemy.attack(player);
            consoleLogic.report(player,enemy);
        }
        else{
            enemy.attack(player);
            player.attack(enemy);
            consoleLogic.report(player,enemy);
        }


        /*while (player.getHp() > 0 && enemy.getHp() > 0){
            if (player.getSpeed() >= enemy.getSpeed()){
                player.attack(enemy);
                enemy.attack(player);
                consoleLogic.report(player,enemy);
            }
            else{
                enemy.attack(player);
                player.attack(enemy);
            }
        }*/
    }
    public void game(){
        player = new Player(300,8,5);
        enemy = new Snake(20,3,3);
        skeleton = new Skeleton(20,3,3);
        ghost = new Ghost(20,3,3);
        snake = new Snake(30,20,1);
        enemyArrayList.add(skeleton);
        enemyArrayList.add(ghost);
        enemyArrayList.add(snake);
        System.out.println("Enter your name\n");
        player.setName(scanner.nextLine());
        enemyChooser(enemyArrayList);
        battle(player, enemyChooser(enemyArrayList));
    }

    public Enemy enemyChooser(ArrayList enemyArrayList){
        Random random = new Random();
        return (Enemy) enemyArrayList.get(random.nextInt(enemyArrayList.size()));
    }

}
