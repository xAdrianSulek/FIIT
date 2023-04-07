package com.example.prosim.entity;

public class Player {
    private static Player single_instance = null;

    private int hp;
    private int dmg;
    private String name;

    private Player(int hp, int dmg){
        this.hp = hp;
        this.dmg = dmg;
    }

    public static synchronized Player getInstance(){
        if (single_instance == null)
            single_instance = new Player(100,30);
        return single_instance;
    }

    public int getHp() {
        return hp;
    }

    public int getDmg() {
        return dmg;
    }

    public void setHp(int hp) {
        this.hp = hp;
    }

    public void setDmg(int dmg) {
        this.dmg = dmg;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
