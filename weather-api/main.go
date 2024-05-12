package main

import (
        "encoding/json"
        "fmt"
        "io/ioutil"
        "log"
        "net/http"
        "os"
)

const baseURL = "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric"

func main() {
        http.HandleFunc("/", getWeather)
        log.Fatal(http.ListenAndServe(":8081", nil))
}

func getWeather(w http.ResponseWriter, r *http.Request) {
        city := r.URL.Query().Get("city")
        if city == "" {
                http.Error(w, "Please provide a city name", http.StatusBadRequest)
                return
        }

        apiKey := os.Getenv("OPENWEATHERMAP_API_KEY")
        if apiKey == "" {
                http.Error(w, "API key not found", http.StatusInternalServerError)
                return
        }

        url := fmt.Sprintf(baseURL, city, apiKey)
        resp, err := http.Get(url)
        if err != nil {
                http.Error(w, err.Error(), http.StatusInternalServerError)
                return
        }
        defer resp.Body.Close()

        body, err := ioutil.ReadAll(resp.Body)
        if err != nil {
                http.Error(w, err.Error(), http.StatusInternalServerError)
                return
        }

        var data map[string]interface{}
        err = json.Unmarshal(body, &data)
        if err != nil {
                http.Error(w, err.Error(), http.StatusInternalServerError)
                return
        }

        json.NewEncoder(w).Encode(data)
}
