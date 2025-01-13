'''
File is reponsible to mimic or interpret Live news API
'''

from flask import Flask, jsonify
import pandas as pd
import os

app = Flask(__name__)

@app.route('/news', methods=['GET'])
def get_news():
    try:
        file_path = 'sample_news.csv'
        if not os.path.exists(file_path):
            return jsonify({"error": "File not found."}), 404
        all_news = pd.read_csv(file_path).to_dict(orient='records')
        return jsonify(all_news)
    except Exception as e:
        return jsonify({"error": "An internal error occured."}), 500


if __name__ == '__main__':
    app.run(port=5000)