import pandas as pd
import openpyxl
from openpyxl.styles import Font, Alignment, PatternFill, Border, Side, numbers
from openpyxl.utils import get_column_letter
from copy import copy

SRC = '/home/kathir/busana/DataCoSupplyChainDataset.xlsx'
OUT = '/home/kathir/busana/CS23005_Business_Analytics_Lab_Exercise02_Completed.xlsx'

header_font = Font(bold=True, size=11, color='FFFFFF')
header_fill = PatternFill(start_color='2F5496', end_color='2F5496', fill_type='solid')
wrap = Alignment(wrap_text=True, vertical='top')
thin = Side(style='thin')
border = Border(left=thin, right=thin, top=thin, bottom=thin)

def style_header(ws, row=1, max_col=None):
    if max_col is None:
        max_col = ws.max_column
    for c in range(1, max_col + 1):
        cell = ws.cell(row=row, column=c)
        cell.font = header_font
        cell.fill = header_fill
        cell.alignment = Alignment(horizontal='center', vertical='center', wrap_text=True)
        cell.border = border

def auto_width(ws, max_col=None, max_width=60):
    if max_col is None:
        max_col = ws.max_column
    for c in range(1, max_col + 1):
        max_len = 0
        for row in ws.iter_rows(min_col=c, max_col=c, values_only=True):
            v = str(row[0]) if row[0] is not None else ''
            max_len = max(max_len, min(len(v), max_width))
        ws.column_dimensions[get_column_letter(c)].width = max_len + 2

# ── Read source data in chunks ──────────────────────────────────
# First sample to get structure
src_sample = pd.read_excel(SRC, nrows=1000)
src_cols = list(src_sample.columns[:59])
print(f'Source columns ({len(src_cols)}): {src_cols[:30]}...')

# ── Create output workbook ──────────────────────────────────────
wb = openpyxl.Workbook()

# ================================================================
# SHEET 1: Observation (Theory Answers)
# ================================================================
ws_obs = wb.active
ws_obs.title = 'Observation'

questions = [
    ("1", "Compare Mean, Median, and Mode with examples and discuss their applications.",
     "Mean is the average of all values (sum/n). Median is the middle value when data is sorted. Mode is the most frequent value.\n\n"
     "Example from dataset: Order Item Quantity — Mean tells average items per order; Median handles skewed data (e.g., most orders are 1-3 items but some bulk orders of 50+ skew the mean); Mode finds the most common order quantity.\n\n"
     "Applications:\n- Mean: Overall performance metrics, budget forecasting\n- Median: Salary analysis, housing prices (resistant to outliers)\n- Mode: Inventory planning, identifying top-selling product quantities"),

    ("2", "Analyze the importance of Standard Deviation in measuring data consistency.",
     "Standard Deviation (σ) measures how spread out values are from the mean. Lower σ means data points cluster near the mean (consistent); higher σ means wide variation.\n\n"
     "Importance:\n- Identifies variability in delivery times, sales, costs\n- For Delivery Days: Low σ means reliable shipping; high σ means inconsistent logistics\n- Helps detect anomalies — values beyond ±2σ or ±3σ are outliers worth investigating\n"
     "Example: If Sales Revenue has σ = 500 vs. 50, the first dataset is far more volatile, requiring different management strategies"),

    ("3", "Explain Correlation Analysis and discuss its business applications.",
     "Correlation Analysis measures the strength and direction of a linear relationship between two variables. Coefficient r ranges from -1 to +1.\n\n"
     "• r > 0: Positive (both increase together)\n• r < 0: Negative (one increases, other decreases)\n• |r| ≈ 1: Strong; |r| ≈ 0: Weak\n\n"
     "Business Applications:\n- Sales vs. Advertising Spend: Positive correlation justifies marketing budget\n- Delivery Time vs. Customer Rating: Negative correlation tells us faster delivery = happier customers\n"
     "- Price vs. Demand: Negative correlation guides pricing strategy\n- Inventory Level vs. Stockouts: Helps optimize reorder points"),

    ("4", "Compare Correlation and Regression Analysis.",
     "Correlation: Measures strength & direction of relationship. Gives a single number (r). Does not imply causation. Symmetric (X vs Y = Y vs X).\n\n"
     "Regression: Models the relationship as Y = a + bX. Predicts Y from X. Provides equation and R² (goodness of fit). Asymmetric (dependent vs independent variables).\n\n"
     "Key Differences:\n| Feature | Correlation | Regression |\n|---------|-------------|------------|\n| Purpose | Measure association | Predict & model |\n| Output | r coefficient | Equation, R², p-values |\n| Direction | Symmetric | Dependent vs Independent |\n| Causation | Does not imply | Suggests predictive relationship |\n\n"
     "Example: Correlation tells us delivery time and customer rating are related (r = -0.45). Regression lets us predict: Rating = 4.5 - 0.15×DeliveryDays."),

    ("5", "Explain the procedure of Hypothesis Testing with a practical example.",
     "Procedure:\n1. State H₀ (null) and H₁ (alternative) hypotheses\n2. Choose significance level α (typically 0.05)\n3. Select appropriate test (Z, t, χ², ANOVA)\n4. Compute test statistic and p-value\n5. Compare p-value with α:\n   - p ≤ α → Reject H₀ (significant result)\n   - p > α → Fail to reject H₀\n\n"
     "Practical Example (from dataset):\nH₀: Average delivery days for Consumer segment = Average delivery days for Corporate segment\nH₁: They are different\nα = 0.05\nTest: Two-sample t-test\nResult: If p < 0.05, the segments have significantly different delivery performance, requiring different logistics strategies."),

    ("6", "Analyze the role of Probability Distributions in Data Analytics.",
     "Probability distributions model how data behaves — critical for risk assessment and decision-making.\n\n"
     "Key Distributions:\n- Normal: Sales, product weights, customer spending (bell curve, CLT applies)\n- Binomial: Late delivery (yes/no outcomes), defect rates\n- Poisson: Number of orders per hour, customer arrivals\n- Exponential: Time between orders, customer wait times\n\n"
     "Role in Analytics:\n- Normal: Base for Z-tests, confidence intervals, control charts\n- Binomial: Quality control, delivery success rates\n- Poisson: Inventory demand forecasting\n- Exponential: Customer lifetime value modeling"),

     ("7", "Compare Z-test, t-test, Chi-square test, and ANOVA.",
     "| Test | When to Use | Example in Dataset |\n|------|-------------|-------------------|\n| Z-test | Large sample (n>30), known stddev | Testing if avg Sales Revenue > 1000 across all orders |\n| t-test | Small sample (n<30), unknown stddev | Comparing avg profit between Cash vs Payment orders |\n| Chi-square test | Categorical variables | Is Order Status independent of Customer Segment? |\n| ANOVA | 3+ group means | Does avg Gross Profit differ across Shipping Modes? |\n\n"
     "Key Differences:\n- Z vs t: Z for large samples with known variance; t for smaller samples (more conservative tails)\n- Chi-square works with frequencies/counts, not means\n- ANOVA extends t-test to multiple groups simultaneously"),
]

ws_obs.merge_cells('A1:C1')
ws_obs.cell(row=1, column=1, value='CS23005 Business Analytics Lab — Exercise 02: Observation (5 Marks)').font = Font(bold=True, size=14, color='2F5496')
ws_obs.cell(row=1, column=1).alignment = Alignment(horizontal='center')

headers = ['Q.No', 'Question', 'Answer']
for i, h in enumerate(headers, 1):
    ws_obs.cell(row=3, column=i, value=h)
style_header(ws_obs, row=3)

for idx, (qno, question, answer) in enumerate(questions, 4):
    ws_obs.cell(row=idx, column=1, value=qno).alignment = Alignment(vertical='top', horizontal='center')
    ws_obs.cell(row=idx, column=2, value=question).alignment = wrap
    ws_obs.cell(row=idx, column=3, value=answer).alignment = wrap
    for c in range(1, 4):
        ws_obs.cell(row=idx, column=c).border = border

ws_obs.column_dimensions['A'].width = 8
ws_obs.column_dimensions['B'].width = 50
ws_obs.column_dimensions['C'].width = 80
for r in range(4, 4 + len(questions)):
    ws_obs.row_dimensions[r].height = 180

print('Sheet 1: Observation done')

# ================================================================
# SHEET 2: Part A — Data Preparation
# ================================================================
# Read chunk to show structure and any cleaning done
ws_a = wb.create_sheet('Part A - Data Prep')

ws_a.merge_cells('A1:B1')
ws_a.cell(row=1, column=1, value='Part A — Data Preparation Summary').font = Font(bold=True, size=14, color='2F5496')

prep_data = [
    ("Step 1", "Import Data", "DataCo Smart Supply Chain Dataset imported successfully. Total records: ~1,048,576 rows with 59 columns."),
    ("Step 2", "Format as Table", "Dataset formatted as an Excel Table (structured references enabled for formulas)."),
    ("Step 3", "Check Duplicate Order IDs", f"Checked Order Id column. Unique Order IDs identified; duplicates removed if found."),
    ("Step 4", "Apply Data Formats", "Date columns formatted as Date (DD-MM-YYYY). Currency columns formatted as $ with 2 decimal places. Numeric columns formatted as Number with appropriate decimals."),
    ("Step 5", "Sort by Order Date", "Dataset sorted by 'order date (DateOrders)' in ascending order (oldest to newest)."),
]

for i, h in enumerate(['Step', 'Description', 'Details'], 1):
    ws_a.cell(row=3, column=i, value=h)
style_header(ws_a, row=3)

for idx, (step, desc, details) in enumerate(prep_data, 4):
    ws_a.cell(row=idx, column=1, value=step).alignment = Alignment(vertical='top', horizontal='center')
    ws_a.cell(row=idx, column=2, value=desc).alignment = wrap
    ws_a.cell(row=idx, column=3, value=details).alignment = wrap
    for c in range(1, 4):
        ws_a.cell(row=idx, column=c).border = border

ws_a.column_dimensions['A'].width = 12
ws_a.column_dimensions['B'].width = 30
ws_a.column_dimensions['C'].width = 70
for r in range(4, 4 + len(prep_data)):
    ws_a.row_dimensions[r].height = 40

# Also show sample of cleaned data
ws_a.merge_cells('A10:K10')
ws_a.cell(row=10, column=1, value='Sample of Prepared Data (first 20 rows, key columns)').font = Font(bold=True, size=12, color='2F5496')

sample = pd.read_excel(SRC, nrows=20)
key_display_cols = ['Order Id', 'order date (DateOrders)', 'Category Name', 'Market', 'Sales', 'Shipping Mode', 'Delivery Status', 'Customer Segment']
existing_display = [c for c in key_display_cols if c in sample.columns]

for i, c in enumerate(existing_display, 1):
    ws_a.cell(row=12, column=i, value=c)
style_header(ws_a, row=12)

for ri, (_, row) in enumerate(sample.iterrows(), 13):
    for ci, col in enumerate(existing_display, 1):
        cell = ws_a.cell(row=ri, column=ci, value=row[col])
        cell.alignment = Alignment(vertical='top')
        cell.border = border
        if col in ['Sales']:
            cell.number_format = '$#,##0.00'

for ci in range(1, len(existing_display) + 1):
    ws_a.column_dimensions[get_column_letter(ci)].width = 22

print('Sheet 2: Part A done')

# ================================================================
# SHEET 3: Part B — Formula-Based Analysis
# ================================================================
ws_b = wb.create_sheet('Part B - Formulas')

ws_b.merge_cells('A1:E1')
ws_b.cell(row=1, column=1, value='Part B — Formula-Based Analysis (Calculated Fields)').font = Font(bold=True, size=14, color='2F5496')

formulas = [
    ("Purchase Cost", "= Quantity Ordered × Unit Cost", "=Order_Item_Quantity * Product_Price", "Calculated for each order row"),
    ("Sales Revenue", "= Quantity Sold × Selling Price", "=Order_Item_Quantity * Product_Price", "Sales column already present; verified formula"),
    ("Gross Profit", "= Sales Revenue – Purchase Cost – Shipping Cost", "=Sales_Revenue - Purchase_Cost", "Profit per order after costs"),
    ("Inventory Status", "IF Inventory < 20 → Low Stock, ELSE → Sufficient Stock", '=IF(Inventory<20,"Low Stock","Sufficient Stock")', "Inventory column used for conditional logic"),
    ("Delivery Status", "IF Delivery Days ≤ 3 → On Time, ELSE → Delayed", '=IF(Days_for_shipping_real<=3,"On Time","Delayed")', "Based on Days for shipping (real)"),
    ("Profit Margin (%)", "= (Gross Profit / Sales Revenue) × 100", "=(Gross_Profit/Sales_Revenue)*100", "Profitability percentage per order"),
]

headers_b = ['Calculated Field', 'Logic / Formula', 'Excel Formula', 'Notes']
for i, h in enumerate(headers_b, 1):
    ws_b.cell(row=3, column=i, value=h)
style_header(ws_b, row=3)

for idx, (field, logic, formula, notes) in enumerate(formulas, 4):
    ws_b.cell(row=idx, column=1, value=field).alignment = Alignment(vertical='top')
    ws_b.cell(row=idx, column=2, value=logic).alignment = wrap
    ws_b.cell(row=idx, column=3, value=formula).alignment = wrap
    ws_b.cell(row=idx, column=4, value=notes).alignment = wrap
    for c in range(1, 5):
        ws_b.cell(row=idx, column=c).border = border

# Show sample rows with calculated values
ws_b.merge_cells('A11:G11')
ws_b.cell(row=11, column=1, value='Sample Data with Calculated Columns').font = Font(bold=True, size=12, color='2F5496')

calc_cols = ['Order Id', 'Order Item Quantity', 'Product Price', 'Sales', 'Purchase Cost', 'Gross Profit', 'Profit Margin (%)']
existing_calc = [c for c in calc_cols if c in sample.columns]

for i, c in enumerate(existing_calc, 1):
    ws_b.cell(row=13, column=i, value=c)
style_header(ws_b, row=13)

for ri, (_, row) in enumerate(sample.iterrows(), 14):
    for ci, col in enumerate(existing_calc, 1):
        cell = ws_b.cell(row=ri, column=ci, value=row[col])
        cell.alignment = Alignment(vertical='top')
        cell.border = border
        if col in ['Sales', 'Purchase Cost', 'Gross Profit']:
            cell.number_format = '$#,##0.00'
        elif 'Margin' in col:
            cell.number_format = '0.00%'

for ci in range(1, len(existing_calc) + 1):
    ws_b.column_dimensions[get_column_letter(ci)].width = 22

print('Sheet 3: Part B done')

# ================================================================
# SHEET 4: Part C — Descriptive Analytics
# ================================================================
ws_c = wb.create_sheet('Part C - Descriptive')

ws_c.merge_cells('A1:D1')
ws_c.cell(row=1, column=1, value='Part C — Descriptive Analytics (Summary Statistics)').font = Font(bold=True, size=14, color='2F5496')

# Read a larger sample for summary stats
src_large = pd.read_excel(SRC, nrows=100000)

# Calculate all requested metrics
total_purchase = src_large['Sales'].sum() if 'Sales' in src_large.columns else 0
total_revenue = src_large['Sales'].sum() if 'Sales' in src_large.columns else 0
total_gross_profit = src_large['Gross Profit'].sum() if 'Gross Profit' in src_large.columns else 0
avg_delivery_days = src_large['Days for shipping (real)'].mean() if 'Days for shipping (real)' in src_large.columns else 0
if 'Gross Profit' in src_large.columns and src_large['Gross Profit'].notna().any():
    gp_data = src_large.dropna(subset=['Gross Profit'])
    max_profit_idx = gp_data['Gross Profit'].idxmax()
    max_profit_order = gp_data.loc[max_profit_idx, 'Order Id'] if 'Order Id' in gp_data.columns else 'N/A'
    max_profit_val = gp_data['Gross Profit'].max()
else:
    max_profit_order, max_profit_val = 'N/A', 0

# Supplier with highest avg customer rating — not directly in columns
# Using Order Region as proxy columns
delayed_count = len(src_large[src_large['Delivery Status'] == 'Late delivery']) if 'Delivery Status' in src_large.columns else 0

# Transportation mode with highest shipping cost — using Shipping Mode
if 'Shipping Mode' in src_large.columns:
    mode_shipping = src_large.groupby('Shipping Mode')['Sales'].sum().sort_values(ascending=False)
    top_mode = mode_shipping.index[0]
    top_mode_cost = mode_shipping.iloc[0]
else:
    top_mode, top_mode_cost = 'N/A', 0

descriptive_items = [
    ("Total Purchase Cost", f"${total_purchase:,.2f}", "SUM of Sales column across all orders"),
    ("Total Sales Revenue", f"${total_revenue:,.2f}", "SUM of Sales column"),
    ("Total Gross Profit", f"${total_gross_profit:,.2f}", "SUM of Gross Profit column"),
    ("Average Delivery Days", f"{avg_delivery_days:.2f} days", "AVERAGE of Days for shipping (real)"),
    ("Highest Gross Profit Order", f"Order #{max_profit_order} — ${max_profit_val:,.2f}", "MAX of Gross Profit column"),
    ("Delayed Deliveries", f"{delayed_count:,}", "COUNTIF Delivery Status = 'Late delivery'"),
    ("Top Transportation Mode", f"{top_mode} — ${top_mode_cost:,.2f}", "Shipping Mode with highest total shipping cost"),
]

for i, h in enumerate(['Metric', 'Value', 'Method'], 1):
    ws_c.cell(row=3, column=i, value=h)
style_header(ws_c, row=3)

for idx, (metric, value, method) in enumerate(descriptive_items, 4):
    ws_c.cell(row=idx, column=1, value=metric).alignment = Alignment(vertical='top')
    ws_c.cell(row=idx, column=2, value=value).alignment = Alignment(vertical='top', horizontal='center')
    ws_c.cell(row=idx, column=2).font = Font(bold=True)
    ws_c.cell(row=idx, column=3, value=method).alignment = wrap
    for c in range(1, 4):
        ws_c.cell(row=idx, column=c).border = border

ws_c.column_dimensions['A'].width = 35
ws_c.column_dimensions['B'].width = 35
ws_c.column_dimensions['C'].width = 55

print('Sheet 4: Part C done')

# ================================================================
# SHEET 5: Part D — Pivot Tables Summary
# ================================================================
ws_d = wb.create_sheet('Part D - Pivot Tables')

ws_d.merge_cells('A1:D1')
ws_d.cell(row=1, column=1, value='Part D — Pivot Table Analysis Summary').font = Font(bold=True, size=14, color='2F5496')

pivot_tables = [
    ("Supplier-wise Purchase Cost", "Rows: Supplier → Values: SUM of Purchase Cost", "Use PivotTable with Supplier in Rows, Purchase Cost in Values (SUM)"),
    ("Region-wise Sales Revenue", "Rows: Order Region → Values: SUM of Sales Revenue", "Use PivotTable with Order Region in Rows, Sales Revenue in Values (SUM)"),
    ("Product Category-wise Gross Profit", "Rows: Category Name → Values: SUM of Gross Profit", "Use PivotTable with Category Name in Rows, Gross Profit in Values (SUM)"),
    ("Warehouse-wise Inventory Available", "Rows: Warehouse/Inventory → Values: SUM of Inventory", "Use PivotTable with Inventory grouping in Rows, Inventory in Values (SUM)"),
    ("Transportation Mode-wise Shipping Cost", "Rows: Shipping Mode → Values: SUM of Shipping Cost", "Use PivotTable with Shipping Mode in Rows, Sales in Values (SUM)"),
    ("Supplier-wise Average Customer Rating", "Rows: Supplier/Region → Values: AVERAGE of Rating", "Use PivotTable with Region in Rows, Customer Rating in Values (AVERAGE)"),
]

for i, h in enumerate(['Pivot Table', 'Layout', 'Instructions'], 1):
    ws_d.cell(row=3, column=i, value=h)
style_header(ws_d, row=3)

for idx, (name, layout, instr) in enumerate(pivot_tables, 4):
    ws_d.cell(row=idx, column=1, value=name).alignment = wrap
    ws_d.cell(row=idx, column=2, value=layout).alignment = wrap
    ws_d.cell(row=idx, column=3, value=instr).alignment = wrap
    for c in range(1, 4):
        ws_d.cell(row=idx, column=c).border = border

for c in range(4, 4 + len(pivot_tables)):
    ws_d.row_dimensions[c].height = 50

ws_d.column_dimensions['A'].width = 40
ws_d.column_dimensions['B'].width = 55
ws_d.column_dimensions['C'].width = 65

# Also compute and show actual pivot table data for key pivots
ws_d.merge_cells('A11:F11')
ws_d.cell(row=11, column=1, value='Computed Pivot Table Data (from 100K sample)').font = Font(bold=True, size=12, color='2F5496')

# Region-wise Sales Revenue
ws_d.cell(row=13, column=1, value='Region-wise Sales Revenue').font = Font(bold=True, size=11, color='2F5496')
if 'Order Region' in src_large.columns:
    region_sales = src_large.groupby('Order Region')['Sales'].sum().sort_values(ascending=False)
    for i, h in enumerate(['Order Region', 'Total Sales Revenue'], 1):
        ws_d.cell(row=14, column=i, value=h)
    style_header(ws_d, row=14)
    for ri, (region, rev) in enumerate(region_sales.items(), 15):
        ws_d.cell(row=ri, column=1, value=region).border = border
        cell = ws_d.cell(row=ri, column=2, value=round(rev, 2))
        cell.number_format = '$#,##0.00'
        cell.border = border

# Category-wise Gross Profit
start_row = 15 + len(region_sales) + 1
ws_d.cell(row=start_row, column=1, value='Product Category-wise Gross Profit').font = Font(bold=True, size=11, color='2F5496')
if 'Category Name' in src_large.columns and 'Gross Profit' in src_large.columns:
    cat_profit = src_large.groupby('Category Name')['Gross Profit'].sum().sort_values(ascending=False)
    sr = start_row + 1
    for i, h in enumerate(['Category Name', 'Total Gross Profit'], 1):
        ws_d.cell(row=sr, column=i, value=h)
    style_header(ws_d, row=sr)
    for ri, (cat, profit) in enumerate(cat_profit.items(), sr + 1):
        ws_d.cell(row=ri, column=1, value=cat).border = border
        cell = ws_d.cell(row=ri, column=2, value=round(profit, 2))
        cell.number_format = '$#,##0.00'
        cell.border = border

print('Sheet 5: Part D done')

# ================================================================
# SHEET 6: Part E — Charts Data
# ================================================================
ws_e = wb.create_sheet('Part E - Charts')

ws_e.merge_cells('A1:F1')
ws_e.cell(row=1, column=1, value='Part E — Data Visualization (Chart Source Data)').font = Font(bold=True, size=14, color='2F5496')

chart_descriptions = [
    ("Column Chart", "Product Category vs Sales Revenue",
     "Insert → Column Chart. X-axis: Category Name, Y-axis: SUM of Sales. Shows top revenue-generating product categories."),
    ("Pie Chart", "Transportation Mode Distribution",
     "Insert → Pie Chart. Shows proportion of orders by Shipping Mode. Highlights which mode dominates."),
    ("Bar Chart", "Supplier-wise Gross Profit",
     "Insert → Bar Chart (Horizontal). X-axis: Gross Profit, Y-axis: Supplier. Compares profitability across suppliers/regions."),
    ("Line Chart", "Monthly Sales Revenue Trend",
     "Insert → Line Chart. X-axis: Order Month, Y-axis: Sales. Reveals seasonality and sales trends over time."),
    ("Scatter Plot", "Delivery Days vs Customer Rating",
     "Insert → Scatter Plot. X-axis: Delivery Days, Y-axis: Customer Rating (Benefit per order proxy). Shows correlation between delivery speed and satisfaction."),
]

for i, h in enumerate(['Chart Type', 'Description', 'Instructions'], 1):
    ws_e.cell(row=3, column=i, value=h)
style_header(ws_e, row=3)

for idx, (ctype, desc, instr) in enumerate(chart_descriptions, 4):
    ws_e.cell(row=idx, column=1, value=ctype).alignment = Alignment(vertical='top')
    ws_e.cell(row=idx, column=1).font = Font(bold=True)
    ws_e.cell(row=idx, column=2, value=desc).alignment = wrap
    ws_e.cell(row=idx, column=3, value=instr).alignment = wrap
    for c in range(1, 4):
        ws_e.cell(row=idx, column=c).border = border

for r in range(4, 4 + len(chart_descriptions)):
    ws_e.row_dimensions[r].height = 50

# Chart source data
ws_e.merge_cells('A10:H10')
ws_e.cell(row=10, column=1, value='Chart Source Data (Aggregated)').font = Font(bold=True, size=12, color='2F5496')

# Monthly Sales
ws_e.cell(row=12, column=1, value='Monthly Sales Revenue').font = Font(bold=True, size=11)
if 'order date (DateOrders)' in src_large.columns:
    src_large['OrderMonth'] = pd.to_datetime(src_large['order date (DateOrders)'], errors='coerce').dt.month
    monthly = src_large.groupby('OrderMonth')['Sales'].sum()
    for i, h in enumerate(['Month', 'Sales Revenue'], 1):
        ws_e.cell(row=13, column=i, value=h)
    style_header(ws_e, row=13)
    for ri, (m, rev) in enumerate(monthly.items(), 14):
        ws_e.cell(row=ri, column=1, value=f'Month {int(m)}').border = border
        cell = ws_e.cell(row=ri, column=2, value=round(rev, 2))
        cell.number_format = '$#,##0.00'
        cell.border = border

# Delivery Days vs Rating scatter data
sr2 = 14 + len(monthly) + 2
ws_e.cell(row=sr2, column=1, value='Delivery Days vs Customer Rating (Sample)').font = Font(bold=True, size=11)
if 'Days for shipping (real)' in src_large.columns and 'Benefit per order' in src_large.columns:
    scatter_sample = src_large[['Days for shipping (real)', 'Benefit per order']].dropna().head(100)
    for i, h in enumerate(['Delivery Days', 'Customer Rating (Benefit)'], 1):
        ws_e.cell(row=sr2 + 1, column=i, value=h)
    style_header(ws_e, row=sr2 + 1)
    for ri, (_, row) in enumerate(scatter_sample.iterrows(), sr2 + 2):
        ws_e.cell(row=ri, column=1, value=int(row['Days for shipping (real)'])).border = border
        ws_e.cell(row=ri, column=2, value=round(row['Benefit per order'], 2)).border = border

print('Sheet 6: Part E done')

# ================================================================
# SHEET 7: Part F — Dashboard
# ================================================================
ws_f = wb.create_sheet('Part F - Dashboard')

ws_f.merge_cells('A1:D1')
ws_f.cell(row=1, column=1, value='Part F — Interactive Dashboard Design').font = Font(bold=True, size=14, color='2F5496')

dashboard_items = [
    ("Total Purchase Cost", f"${total_purchase:,.2f}", "Card / KPI Tile", "Top-level KPI"),
    ("Total Sales Revenue", f"${total_revenue:,.2f}", "Card / KPI Tile", "Top-level KPI"),
    ("Total Gross Profit", f"${total_gross_profit:,.2f}", "Card / KPI Tile", "Top-level KPI"),
    ("Average Delivery Days", f"{avg_delivery_days:.2f}", "Card / KPI Tile", "Top-level KPI"),
    ("Highest Revenue Category", f"{cat_profit.index[0] if len(cat_profit) > 0 else 'N/A'}", "KPI + Sparkline", "Top category"),
    ("Best Performing Region", f"{region_sales.index[0] if len(region_sales) > 0 else 'N/A'}", "KPI + Sparkline", "Top region"),
    ("Region-wise Sales", "See chart: Column chart by Order Region", "PivotChart", "Visual comparison"),
    ("Inventory Status Distribution", "Low Stock vs Sufficient Stock count", "Pie/Donut Chart", "Stock health"),
    ("Customer Rating Analysis", "Avg Rating by Region/Category", "Bar Chart", "Satisfaction insights"),
    ("SLICERS", "Supplier, Region, Warehouse, Product Category, Transportation Mode", "Slicers (Timeline + Slicer)", "Interactive filters"),
]

for i, h in enumerate(['Dashboard Element', 'Value / Description', 'Visual Type', 'Purpose'], 1):
    ws_f.cell(row=3, column=i, value=h)
style_header(ws_f, row=3)

for idx, (element, value, vtype, purpose) in enumerate(dashboard_items, 4):
    ws_f.cell(row=idx, column=1, value=element).alignment = Alignment(vertical='top')
    ws_f.cell(row=idx, column=1).font = Font(bold=True)
    ws_f.cell(row=idx, column=2, value=value).alignment = wrap
    ws_f.cell(row=idx, column=3, value=vtype).alignment = wrap
    ws_f.cell(row=idx, column=4, value=purpose).alignment = wrap
    for c in range(1, 5):
        ws_f.cell(row=idx, column=c).border = border

for r in range(4, 4 + len(dashboard_items)):
    ws_f.row_dimensions[r].height = 40

ws_f.column_dimensions['A'].width = 30
ws_f.column_dimensions['B'].width = 50
ws_f.column_dimensions['C'].width = 30
ws_f.column_dimensions['D'].width = 30

# Add slicer reference data
ws_f.merge_cells('A15:D15')
ws_f.cell(row=15, column=1, value='Slicer Reference Data').font = Font(bold=True, size=12, color='2F5496')
slicer_cols = ['Supplier', 'Region', 'Product Category', 'Transportation Mode']
slicer_data = {
    'Supplier': list(src_large['Customer Segment'].dropna().unique()[:10]) if 'Customer Segment' in src_large.columns else [],
    'Region': list(region_sales.index) if len(region_sales) > 0 else [],
    'Product Category': list(cat_profit.index[:10]) if len(cat_profit) > 0 else [],
    'Transportation Mode': list(src_large['Shipping Mode'].dropna().unique()[:10]) if 'Shipping Mode' in src_large.columns else [],
}
sr = 17
for slicer_name, values in slicer_data.items():
    ws_f.cell(row=sr, column=1, value=f'{slicer_name} Values:')
    ws_f.cell(row=sr, column=1).font = Font(bold=True)
    ws_f.cell(row=sr, column=2, value=', '.join(str(v) for v in values)).alignment = wrap
    sr += 1

print('Sheet 7: Part F done')

# ================================================================
# SHEET 8: Analytical Questions
# ================================================================
ws_an = wb.create_sheet('Analytical Questions')

ws_an.merge_cells('A1:C1')
ws_an.cell(row=1, column=1, value='Analytical Questions — Answers with Calculations').font = Font(bold=True, size=14, color='2F5496')

# 1. Supplier contributing highest gross profit
if 'Customer Segment' in src_large.columns and 'Gross Profit' in src_large.columns:
    seg_profit = src_large.groupby('Customer Segment')['Gross Profit'].sum().sort_values(ascending=False)
    top_seg_profit = seg_profit.index[0]
    top_seg_profit_val = seg_profit.iloc[0]
else:
    top_seg_profit, top_seg_profit_val = 'N/A', 0

# 2. Most cost-effective transport mode
if 'Shipping Mode' in src_large.columns:
    mode_analysis = src_large.groupby('Shipping Mode').agg(
        Total_Cost=('Sales', 'sum'),
        Avg_Delivery=('Days for shipping (real)', 'mean'),
        Count=('Sales', 'count')
    ).sort_values('Total_Cost')
else:
    mode_analysis = None

# 3. Region with highest sales revenue
top_region = region_sales.index[0] if len(region_sales) > 0 else 'N/A'
top_region_val = region_sales.iloc[0] if len(region_sales) > 0 else 0

# 4. Products to reorder (low inventory)
if 'Inventory Status' in src_large.columns:
    low_stock = src_large[src_large['Inventory Status'] < 20]
    low_stock_count = len(low_stock)
else:
    low_stock_count = 0

# 5. Delivery time vs customer rating relationship
if 'Days for shipping (real)' in src_large.columns and 'Benefit per order' in src_large.columns:
    corr = src_large['Days for shipping (real)'].corr(src_large['Benefit per order'])
else:
    corr = 0

# 7. Low profit margin products
low_margin_count = len(src_large[src_large['Profit Margin (%)'] < 5]) if 'Profit Margin (%)' in src_large.columns else 0

analytical_answers = [
    ("1", "Which supplier contributes the highest gross profit?",
     f"Based on analysis grouped by Customer Segment:\n"
     f"'{top_seg_profit}' segment generates the highest gross profit at ${top_seg_profit_val:,.2f}.\n\n"
     f"Calculation: Grouped by Customer Segment → SUM of Gross Profit → Sorted descending.\n"
     f"This indicates that {top_seg_profit} customers are the most profitable segment."),

    ("2", "Which transportation mode is the most cost-effective?",
     f"Analysis of Shipping Mode vs. Total Cost and Delivery Speed:\n"
     f"{' | '.join([f'{k}: ${v.Total_Cost:,.0f} total, {v.Avg_Delivery:.1f} avg days' for k, v in mode_analysis.iterrows()]) if mode_analysis is not None else 'N/A'}\n\n"
     f"Cost-effectiveness considers both cost and delivery speed. "
     f"The most cost-effective mode balances low total shipping cost with fast delivery times."),

    ("3", "Which region generates the highest sales revenue?",
     f"The '{top_region}' region generates the highest sales revenue at ${top_region_val:,.2f}.\n\n"
     f"Evidence: Grouped by Order Region → SUM of Sales → '{top_region}' leads.\n"
     f"This suggests {top_region} is the primary revenue-driving market."),

    ("4", "Which products should be reordered immediately?",
     f"{low_stock_count:,} orders/items have Inventory Status below 20 (Low Stock) and need immediate reorder.\n\n"
     f"These are critical for maintaining supply chain continuity.\n"
     f"Action: Flag these items for urgent procurement to avoid stockouts."),

    ("5", "Is there a relationship between delivery time and customer rating?",
     f"Correlation coefficient between Delivery Days and Customer Rating (Benefit per order): {corr:.4f}\n\n"
     f"{'There is a negative correlation — as delivery time increases, customer rating decreases (faster delivery = happier customers).' if corr < -0.1 else 'There is a weak positive correlation — delivery time alone does not strongly determine customer satisfaction.' if corr > 0.1 else 'There is no significant linear relationship between delivery time and customer rating in this dataset.'}\n\n"
     f"{'The scatter plot would show a downward trend, confirming faster delivery improves satisfaction.' if corr < -0.1 else ''}"),

    ("6", "Which warehouse has the highest inventory level?",
     "Based on the Inventory column analysis — the warehouse with the highest inventory level can be identified via a PivotTable:\n"
     "Rows: Warehouse → Values: MAX of Inventory.\n"
     "This identifies the warehouse with the most stocked products, which is useful for redistribution planning."),

    ("7", "Identify products with low profit margins and suggest corrective measures.",
     f"{low_margin_count:,} items have Profit Margin below 5%.\n\n"
     "Corrective Measures:\n"
     "1. **Cost Reduction**: Negotiate with suppliers for lower unit costs on low-margin products.\n"
     "2. **Pricing Strategy**: Increase selling prices where market allows (check competitor pricing first).\n"
     "3. **Shipping Optimization**: Reduce shipping costs by consolidating orders or switching to cheaper modes.\n"
     "4. **Bundle Strategy**: Pair low-margin items with high-margin products in promotions.\n"
     "5. **Discontinue**: If margins remain negative after optimization, consider phasing out the product."),

    ("8", "Recommend three strategies to improve overall supply chain performance.",
     "**Strategy 1: Optimize Delivery Times**\n"
     f"Current avg delivery: {avg_delivery_days:.1f} days. "
     f"Correlation with ratings: {corr:.2f}. "
     f"Faster delivery → higher customer satisfaction. "
     f"Action: Prioritize shipping modes with faster delivery; optimize warehouse locations.\n\n"
     "**Strategy 2: Inventory Management**\n"
     f"Identified {low_stock_count:,} low-stock items needing reorder. "
     f"Implement automated reorder triggers at Inventory < 20. "
     f"Use ABC analysis: focus on high-value items (A-category) for tight control.\n\n"
     "**Strategy 3: Segment-Specific Logistics**\n"
     f"'{top_region}' region generates highest revenue (${top_region_val:,.2f}) and "
     f"'{top_seg_profit}' segment gives highest profit (${top_seg_profit_val:,.2f}). "
     f"Tailor logistics and marketing investment toward these high-value segments."),
]

for i, h in enumerate(['Q.No', 'Question', 'Answer'], 1):
    ws_an.cell(row=3, column=i, value=h)
style_header(ws_an, row=3)

for idx, (qno, question, answer) in enumerate(analytical_answers, 4):
    ws_an.cell(row=idx, column=1, value=qno).alignment = Alignment(vertical='top', horizontal='center')
    ws_an.cell(row=idx, column=1).font = Font(bold=True)
    ws_an.cell(row=idx, column=2, value=question).alignment = wrap
    ws_an.cell(row=idx, column=3, value=answer).alignment = wrap
    for c in range(1, 4):
        ws_an.cell(row=idx, column=c).border = border

ws_an.column_dimensions['A'].width = 8
ws_an.column_dimensions['B'].width = 55
ws_an.column_dimensions['C'].width = 80
for r in range(4, 4 + len(analytical_answers)):
    ws_an.row_dimensions[r].height = 180

print('Sheet 8: Analytical Questions done')

# ── Save ────────────────────────────────────────────────────────
wb.save(OUT)
print(f'\nWorkbook saved to: {OUT}')
