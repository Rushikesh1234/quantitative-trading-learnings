from flask import Flask, jsonify, request

app = Flask(__name__)

# ---------- ACCOUNTS ---------- #

# Endpoint 1.1: Signatures and Owners
@app.route('/iserver/<accountId>/signatures-and-owners', methods=['GET'])
def signatures_and_owners(accountId):
    if accountId == "U1234567":
        return jsonify({
            "accountId": accountId,
            "users": [
                {
                    "roleId": "OWNER",
                    "hasRightCodeInd": True,
                    "entity": {
                        "entityType": "INDIVIDUAL",
                        "entityName": "John Smith",
                        "firstName": "John",
                        "lastName": "Smith"
                    }
                }
            ],
            "applicant": {
                "signatures": ["John Smith"]
            }
        }), 200
    else:
        return jsonify({"error": "Invalid accountId", "statusCode": 503}), 503

# Endpoint 1.2: Switch Account
@app.route('/iserver/account', methods=['POST'])
def switch_account():
    data = request.json
    if data and data.get("acctId") == "U1234567":
        return jsonify({"set": True, "acctId": "U2234567"}), 200
    elif not data or "acctId" not in data:
        return jsonify({"error": "Invalid account ID"}), 500
    else:
        return jsonify({"error": "string", "statusCode": "string"}), 503

# Endpoint 1.3: Account Profit and Loss
@app.route('/iserver/account/pnl/partitioned', methods=['GET'])
def account_pnl_partitioned():
    return jsonify({
        "upnl": {
            "U1234567.Core": {
                "rowType": 1,
                "dpl": -12510,
                "nl": 1290000,
                "upl": 256000,
                "el": 824600,
                "mv": 1700000
            }
        }
    }), 200

# Endpoint 1.4: Account Market Value Summary
@app.route('/iserver/account/<accountId>/summary/market_value', methods=['GET'])
def account_market_value(accountId):
    if accountId == "U1234567":
        return jsonify({
            "EUR": {"total_cash": "194", "net_liquidation": "194"},
            "USD": {"total_cash": "-401,958", "net_liquidation": "1,289,161"},
        }), 200
    elif not accountId or accountId != "U1234567":
        return jsonify({"error": "Bad Request: accountId is not valid: 11110000", "statusCode": 400}), 400
    else:
        return jsonify({"error": "string", "statusCode": "string"}), 503

# ---------- MARKET DATA ---------- #

# Endpoint 2.1: Request Historical Data
@app.route('/iserver/marketdata/history', methods=['GET'])
def marketdata_history():
    return jsonify({
        "serverid": "20477",
        "symbol": "AAPL",
        "text": "APPLE INC",
        "startTime": "20230818-08:00:00",
        "data": [
            {
                "t": 1692345600000,
                "o": 173.4,
                "c": 174.7,
                "h": 175.1,
                "l": 171.7,
                "v": 472117.45
            }
        ],
        "points": 1,
    }), 200

# Endpoint 2.2: Live Market Data Snapshot
@app.route('/iserver/marketdata/snapshot', methods=['GET'])
def marketdata_snapshot():
    return jsonify({"V": 0, "T": 0}), 200

# ---------- SESSION MANAGEMENT ---------- #

# Endpoint 3.1: Initialize Brokerage Session
@app.route('/iserver/auth/ssodh/init', methods=['POST'])
def initialize_session():
    data = request.json
    if data and data.get("publish") and data.get("compete"):
        return jsonify({
            "success": {
                "value": {
                    "authenticated": True,
                    "competing": False,
                    "connected": True,
                    "message": "",
                    "MAC": "98:F2:B3:23:BF:A0",
                    "serverInfo": {
                        "serverName": "JifN19053",
                        "serverVersion": "Build 10.25.0p, Dec 5, 2023 5:48:12 PM"
                    }
                }
            }
        }), 200
    else:
        return jsonify({"error": "string"}), 500

# Endpoint 3.2: Brokerage Session Auth Status
@app.route('/iserver/auth/status', methods=['POST'])
def session_auth_status():
    return jsonify({
        "success": {
            "value": {
                "authenticated": True,
                "competing": False,
                "connected": True,
                "message": "",
                "MAC": "12:B:B3:23:BF:A0",
                "serverInfo": {
                    "serverName": "JifN19053",
                    "serverVersion": "Build 10.25.0p, Dec 5, 2023 5:48:12 PM"
                },
                "fail": ""
            }
        }
    }), 200

if __name__ == '__main__':
    app.run(port=5000)
