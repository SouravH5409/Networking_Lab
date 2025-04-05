# 🌐 Computer Network Programs & Simulations

This repository contains a collection of computer networking programs implemented in C and networking simulations .
---

## 📂 Project Structure

Each folder contains source code and simulation files demonstrating key network protocols and models:

| Module / Protocol        | Description |
|--------------------------|-------------|
| **DVR**                  | Distance Vector Routing algorithm implemented in C. |
| **FTP**                  | Basic File Transfer Protocol (FTP) server implementation. |
| **GoBackN**              | Go-Back-N ARQ protocol simulation. |
| **LeakyBucket**          | Leaky Bucket algorithm to simulate traffic shaping. |
| **Link State Routing**   | Link State Routing algorithm simulation (e.g., OSPF-like). |
| **NS2**                  | Network Simulator 2 (NS2) TCL script for simulating network topologies. |
| **Selective Repeat ARQ** | Simulation of Selective Repeat Automatic Repeat reQuest protocol. |
| **Stop and Wait**        | Stop-and-Wait ARQ protocol simulation. |
| **TCP**                  | Simple TCP client-server time synchronization example. |
| **UDP**                  | UDP-based program to demonstrate message exchange. |

---

## 🚀 Running the Programs

## For Client_Server Programs:
Compile using `gcc`:
```bash
gcc -o server server.c
./server
```
```
gcc -o client client.c
./client
```
