package com.example.prosim.entity;

public  abstract class Enemy {
    int hp;
    int dmg;
    int speed;
    String name;

    public Enemy(int hp, int dmg, int speed) {
        this.hp = hp;
        this.dmg = dmg;
        this.speed = speed;
    }

    public int getHp() {
        return hp;
    }

    public int getDmg() {
        return dmg;
    }

    public int getSpeed() {
        return speed;
    }

    public String getName() {
        return name;
    }

    public void setHp(int hp) {
        this.hp = hp;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDmg(int dmg) {
        this.dmg = dmg;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }



    public void attack(Player player){}
}
