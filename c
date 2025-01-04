<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Pagamento PIX - HoloFi</title>
    <link rel="icon" href="https://nscsuport.github.io/OZZ/z.png" type="image/x-icon">
  <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }

        body {
            font-family: 'Roboto', Arial, sans-serif;
            background-color: #000;
            color: #00FF00;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            flex-direction: column;
            padding: 10px;
            zoom: 70%;
        }

        h1 {
            font-size: 2.8rem;
            margin: 20px 0;
            color: #00FF00;
            text-align: center;
            text-shadow: 0 0 20px #7e00ff;
        }

        .container {
            width: 100%;
            max-width: 600px;
            background-color: #1e1e1e;
            border-radius: 12px;
            padding: 25px;
            box-shadow: 0 6px 20px rgba(0, 0, 0, 0.6);
            margin: 0 auto;
        }

        .form-group {
            margin-bottom: 20px;
        }

        .form-group label {
            display: block;
            margin-bottom: 8px;
            font-weight: bold;
            color: #e0e0e0;
        }

        .form-group input, .form-group select {
            width: 100%;
            padding: 12px;
            border-radius: 8px;
            border: 1px solid #3c3c3c;
            background-color: #2a2a2a;
            color: #e0e0e0;
            font-size: 1.1rem;
            transition: border-color 0.3s ease;
        }

        .form-group input:focus, .form-group select:focus {
            outline: none;
            border-color: #4CAF50;
        }

        .buttons-group {
            display: flex;
            justify-content: space-between;
            gap: 10px;
            margin-top: 20px;
        }

        .buttons-group button {
            padding: 14px;
            border-radius: 8px;
            font-weight: bold;
            cursor: pointer;
            color: #fff;
            border: none;
            transition: background-color 0.3s ease, transform 0.3s ease;
            text-align: center;
            flex: 1;
        }

        .btn-green {
            background-color: #4CAF50;
        }

        .btn-green:hover {
            background-color: #45a049;
            transform: scale(1.05);
        }

        .btn-red {
            background-color: #f44336;
        }

        .btn-red:hover {
            background-color: #d32f2f;
            transform: scale(1.05);
        }

        .qr-code-container {
            margin-top: 20px;
            padding: 20px;
            width: 100%;
            background-color: #0000aa;
            color: #ffffff;
            font-family: 'Courier New', Courier, monospace;
            font-size: 1.1rem;
            border-radius: 8px;
            text-align: center;
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.5);
        }

        footer {
            width: 100%;
            padding: 20px;
            background: linear-gradient(45deg, #f0f000, #ff4500);
            color: #000000;
            text-align: center;
            font-size: 1.1rem;
            font-weight: bold;
            letter-spacing: 2px;
            text-shadow: 0 0 5px #ff0000, 0 0 10px #ff0000, 0 0 15px #ff0000;
            margin-top: 20px;
            animation: neon 1.5s ease-in-out infinite alternate;
        }

        footer a {
            color: #000000;
            text-decoration: none;
        }

        footer a:hover {
            text-decoration: underline;
        }

        @keyframes neon {
            0% {
                text-shadow: 0 0 5px #ff0000, 0 0 10px #ff0000, 0 0 15px #ff0000;
            }
            50% {
                text-shadow: 0 0 20px #ff0000, 0 0 30px #ff4500, 0 0 40px #f0f000;
            }
            100% {
                text-shadow: 0 0 5px #ff0000, 0 0 10px #ff0000, 0 0 15px #ff0000;
            }
        }

        @media (max-width: 600px) {
            h1 {
                font-size: 2rem;
            }

            .container {
                padding: 15px;
            }

            .form-group input, .form-group select {
                padding: 10px;
                font-size: 1rem;
            }

            .buttons-group {
                flex-direction: column;
            }

            .buttons-group button {
                margin-bottom: 10px;
            }

            footer {
                font-size: 1rem;
            }
        }
    </style>
</head>
<body>
    <h1>Pagamento PIX - HoloFi</h1>
    <div class="container">
        <div class="form-group">
            <label for="investment-value">Valor do Investimento (R$)</label>
            <input type="number" id="investment-value" placeholder="Digite o valor investido" min="1" step="0.01" required>
        </div>

        <div class="form-group">
            <label for="profit">Lucro Esperado (%)</label>
            <input type="number" id="profit" placeholder="Digite o lucro em %" min="1" max="1000" value="1000" readonly>
        </div>

        <div class="form-group">
            <label for="pix-key">Chave PIX de Cobrança</label>
            <input type="text" id="pix-key" placeholder="Insira a chave PIX" required>
        </div>

        <div class="buttons-group">
            <button class="btn-green" id="generate-code-btn">Gerar Código PIX</button>
            <button class="btn-red" id="confirm-btn">Confirmar Compra</button>
        </div>

        <div class="qr-code-container" id="qrcode-container">
            <p>Gerando Código...</p>
        </div>

        <footer>
            <p>© 2025 HoloFi | Todos os direitos reservados.</p>
            <p><a href="https://www.holofi.com">Visite nosso site</a></p>
        </footer>
    </div>

    <script>
        // Função de Fibonacci Geminiana (sequência alternada)
        function fibonacciGeminiana(n) {
            let a = 0, b = 1;
            let result = [a, b];
            for (let i = 2; i <= n; i++) {
                let temp = a + b;
                a = b;
                b = temp;
                result.push(b);
                if (i % 2 === 0) {
                    result.push(a);  // Duplicando o valor alternadamente
                }
            }
            return result;
        }

        document.getElementById('generate-code-btn').addEventListener('click', async function() {
            const value = parseFloat(document.getElementById('investment-value').value);
            const profit = 1000; // Lucro fixo em 1000%
            const pixKey = document.getElementById('pix-key').value;

            // Validação de campos
            if (!value || !pixKey) {
                alert("Por favor, preencha todos os campos.");
                return;
            }

            // Cálculo do lucro
            const calculatedProfit = value * (profit / 100);
            const totalAmount = value + calculatedProfit;

            // Gerando a Fibonacci Geminiana (sequência alternada)
            const fibonacciSequence = fibonacciGeminiana(10);  // Gerando os 10 primeiros números

            // Simulação do uso de Detrix como oráculo (simulação simples)
            const detrixResult = `Oráculo Detrix: Lucro de ${calculatedProfit.toFixed(2)} R$ calculado com base no investimento.`;

            // Exibindo o resultado
            const qrCodeData = {
                pixKey: pixKey,
                amount: totalAmount.toFixed(2),
                description: `Investimento: R$${value.toFixed(2)} + Lucro: R$${calculatedProfit.toFixed(2)}`
            };

            const qrCodeContainer = document.getElementById('qrcode-container');
            qrCodeContainer.innerHTML = `
                <p><strong>Código PIX para pagamento:</strong></p>
                <pre>${JSON.stringify(qrCodeData, null, 2)}</pre>
                <p><strong>Total a ser pago: R$ ${totalAmount.toFixed(2)}</strong></p>
                <p>${detrixResult}</p>
                <p><strong>Sequência Fibonacci Geminiana:</strong> ${fibonacciSequence.join(', ')}</p>
            `;

            // Integrando Mercado Pago
            try {
                const response = await fetch('https://api.mercadopago.com/checkout/preferences', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                        'Authorization': 'APP_USR-5426605333181809-010315-b06229d80c1e63ed582dbd28e27c677a-1658720398',
                    },
                    body: JSON.stringify({
                        items: [
                            {
                                title: `Investimento HoloFi`,
                                quantity: 1,
                                unit_price: totalAmount,
                                currency_id: 'BRL',
                            },
                        ],
                        back_urls: {
                            success: 'http://www.holofi.com/success',
                            failure: 'http://www.holofi.com/failure',
                            pending: 'http://www.holofi.com/pending',
                        },
                        payer_email: pixKey, // Coloque aqui o email do comprador
                    }),
                });

                const data = await response.json();
                const initPoint = data.init_point; // URL de pagamento gerada pelo Mercado Pago

                qrCodeContainer.innerHTML += `
                    <p><strong>Pagamento Mercado Pago:</strong> <a href="${initPoint}" target="_blank">Clique aqui para realizar o pagamento</a></p>
                `;
            } catch (error) {
                console.error("Erro ao gerar pagamento no Mercado Pago:", error);
                qrCodeContainer.innerHTML += `<p>Erro ao gerar pagamento Mercado Pago. Tente novamente.</p>`;
            }
        });

        document.getElementById('confirm-btn').addEventListener('click', function() {
            alert("Compra confirmada com sucesso!");
            // Integrar a API de pagamento do Mercado Pago aqui.
        });
    </script>
</body>
</html>
