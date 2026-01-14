# Vending Machine Simulator (C++ Project)

This is a **console-based Vending Machine simulator** implemented in C++ using Visual Studio 2022.  
It simulates a real vending machine with multiple roles, file handling, and cash management.

---

## Features

- **Three Modes of Operation:**
  1. **Customer:** View products, buy items, add balance, and get change.
  2. **Stock Manager:** Refill slots, update products, remove products, refill entire machine.
  3. **Admin:** Manage products, money in the machine, and view machine status.

- **File Handling:**  
  - Product data for each row (A-J) stored in `A.txt`, `B.txt`, …, `J.txt`.  
  - Change/notes are stored in `change.txt`.  
  - Default products stored in `defp.txt`.

- **Data Structures Used:**  
  - **Linked lists** for storing multiple products per slot.  
  - Arrays for machine slots and note denominations.  

- **Dynamic Operations:**  
  - Add, update, remove products.  
  - Manage cash notes and return correct change.  
  - Refill entire machine from a master file.

---

## How to Run

1. Open the project in **Visual Studio 2022**.
2. Make sure the following files are in the project folder:
   - `A.txt` to `J.txt` (row-wise products)
   - `change.txt` (machine balance)
   - `defp.txt` (default products)
3. Build the project (F7 or **Build → Build Solution**).
4. Run the project (F5 or **Debug → Start Debugging**).
5. Follow the console menu to interact as a **Customer**, **Stock Manager**, or **Admin**.

---

## Credentials

- **Admin passkey:** `Vendee`
- **Stock Manager passkey:** `Stockee`

---

