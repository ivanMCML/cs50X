import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user's stock balance
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS amount FROM history WHERE user_id=? GROUP BY symbol HAVING amount>0",
        session["user_id"])

    # Get user's cash balance
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]

    totalValue = cash

    # Get stock names and prices for symbols
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        # Update totalValue
        totalValue = totalValue + stock["amount"] * stock["price"]

    return render_template("index.html", stocks=stocks, totalValue=usd(totalValue), cash=usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # If method is post
    if request.method == "POST":

        # Check if user entered symbol
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("Symbol required", 400)

        # Check if user entered shares as number
        shares = request.form.get("shares")
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Shares must be a positive number", 400)

        # Check if entered symbol exists
        quote = lookup(symbol)
        if not quote:
            return apology("Invalid symbol")

        # Get total value of user's stock
        price = quote["price"]
        cost = price * int(shares)

        # Get user's cash balance and check if user has enough cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", (session["user_id"],))[0]["cash"]
        if cash < cost:
            return apology("Insufficient balance")

        # Update user's cash balance after transaction
        db.execute("UPDATE users SET cash=? WHERE id=?", cash-cost, session["user_id"])

        # Update user stock balance after transaction
        db.execute("INSERT INTO history(user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"], symbol, int(shares), price)

        # Create a message
        flash(f"You bought {shares} shares of {symbol} worth {usd(cost)}.")
        return redirect("/")

    # If method is get
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get history of user's transactions
    transactions = db.execute(
        "SELECT symbol, shares, price, date FROM history WHERE user_id=? ORDER BY date DESC",
        session["user_id"]
    )

    # Get names of user's stocks and get types of transactions
    for trans in transactions:
        trans["name"] = lookup(trans["symbol"])["name"]
        if trans["shares"] < 0:
            trans["type"] = "sold"
        else:
            trans["type"] = "bought"

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # If method is post
    if request.method == "POST":

        # Get stock symbol and informations
        symbol = request.form.get("symbol").upper()
        quote = lookup(symbol)

        # Check if symbol exists
        if not quote:
            return apology("Invalid symbol")

        return render_template("quote.html", quote=quote)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # clear previous session
    session.clear()

    # If method is post
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("Must provide username", 400)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("Must provide password", 400)

        # Ensure password comfirmation was submitted
        confirm = request.form.get("confirmation")
        if not confirm:
            return apology("You must confirm your password", 400)

        # Ensure passwords match
        if password != confirm:
            return apology("Passwords do not match", 400)

        # Search for duplicate
        rows = db.execute("SELECT username FROM users WHERE username=?", username)
        if rows:
            return apology("Username already exists", 400)

        # Insert new user into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   username, generate_password_hash(password))

        # Start session for new user
        rows = db.execute("SELECT * FROM users WHERE username=?", username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    # If method is get
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get users stock wallet
    stocks = db.execute("SELECT symbol, SUM(shares) as amount FROM history WHERE user_id=? GROUP BY symbol HAVING amount>0",
                        session["user_id"])

    # If method is post
    if request.method == "POST":

        # Get symbol and shares user want to sell
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check if user entered valid values
        if not symbol:
            return apology("Symbol required")
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Amount must be a positive number")

        for stock in stocks:

            # Find the stock user wants to sell
            if stock["symbol"] == symbol:

                # Check if user had enough stocks
                if stock["amount"] >= int(shares):
                    stockData = lookup(symbol)
                    if not stockData:
                        return apology("Symbol doesn't exist")

                    # Update user's cash and stock balance
                    db.execute("UPDATE users SET cash= cash + ? WHERE id=?",
                               stockData["price"] * int(shares), session["user_id"])
                    db.execute("INSERT INTO history(user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
                               session["user_id"], symbol, int(shares)*(-1), stockData["price"])

                    # Inform user about successful transaction
                    flash(f"You sold {shares} {symbol} for {usd(stockData['price'] * int(shares))}")
                    return redirect("/")

                else:
                    return apology("You don't have enough shares")

    # If method is get
    else:
        return render_template("sell.html", stocks=stocks)
