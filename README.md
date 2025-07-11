# Book Shop Management System

A simple terminal-based C++ application for managing a bookstore with admin and customer roles. This project includes functionality for managing books, user authentication, and file persistence using `books.txt` and `users.txt`.

---

## Features

### User System
- Login & Sign-Up support
- Role-based access: `admin` and `customer`
- Auto-persist new users to `users.txt`

### Book Inventory
- Add, Edit, Remove books (admin)
- Search by title & author
- Sort books alphabetically
- Price-based filtering
- Purchase books (updates stock)
- Persist book data in `books.txt`

### File Storage
- `users.txt` → Stores registered users with role
- `books.txt` → Stores all book records (auto-generated on save)

---

## 🛠️ How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/bookshop-management.git
   cd bookshop-management
